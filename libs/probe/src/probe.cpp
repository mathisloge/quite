#include "quite/probe.hpp"
#include <QCoreApplication>
#include <thread>
#include <QtCore/private/qhooks_p.h>
#include <agrpc/asio_grpc.hpp>
#include <asio/compose.hpp>
#include <exec/finally.hpp>
#include <exec/task.hpp>
#include <fmt/compile.h>
#include <fmt/format.h>
#include <grpcpp/server_builder.h>
#include <quite/proto/probe.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "injector/mouse_injector.hpp"
#include "object_tracker.hpp"
#include "rpc/create_snapshot.hpp"
#include "rpc/exit_request.hpp"
#include "rpc/find_object.hpp"
#include "rpc/get_object_properties.hpp"
#include "rpc/get_views.hpp"
#include "rpc/mouse_action.hpp"
#include "value_converters.hpp"
namespace
{

using RpcFindObjectSender = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;

struct ProbeData final
{
    ProbeData(grpc::ServerBuilder builder = {})
        : grpc_context{builder.AddCompletionQueue()}
        , tracker{std::make_shared<quite::ObjectTracker>()}
        , mouse_injector{std::make_shared<quite::probe::MouseInjector>(tracker)}
    {
        using namespace quite;
        builder.RegisterService(&object_service);
        builder.AddListeningPort("unix:///tmp/grpc_probe.sock", grpc::InsecureServerCredentials());
        server = builder.BuildAndStart();

        grpc_runner = std::jthread{[this]() {
            auto find_obj_rpc = quite::probe::find_object(grpc_context, object_service, *tracker);
            auto get_object_properties_rpc =
                quite::probe::get_object_properties(grpc_context, object_service, *tracker);
            auto mouse_action_rpc = quite::probe::mouse_action(grpc_context, object_service, *mouse_injector);
            auto create_snapshot_rpc = quite::probe::create_snapshot(grpc_context, object_service, *tracker);
            auto get_views_rpc = quite::probe::get_views(grpc_context, object_service, *tracker);
            auto exit_request_rpc = quite::probe::exit_request(grpc_context, object_service);

            grpc_context.work_started();
            auto snd = exec::finally(stdexec::when_all(std::move(find_obj_rpc),
                                                       std::move(get_object_properties_rpc),
                                                       std::move(mouse_action_rpc),
                                                       std::move(create_snapshot_rpc),
                                                       std::move(get_views_rpc),
                                                       std::move(exit_request_rpc)),
                                     stdexec::then(stdexec::just(), [this] { grpc_context.work_finished(); }));
            stdexec::sync_wait(
                stdexec::when_all(std::move(snd), stdexec::then(stdexec::just(), [&] { grpc_context.run(); })));
            spdlog::error("CLOSING GRPC");
        }};
    }

    ~ProbeData() = default;

    void exit()
    {
        server->Shutdown(std::chrono::system_clock::now() + std::chrono::seconds{2});
        server->Wait();
        grpc_context.stop();

        server = nullptr;
        mouse_injector = nullptr;
    }

    agrpc::GrpcContext grpc_context;
    std::unique_ptr<grpc::Server> server;
    std::shared_ptr<quite::ObjectTracker> tracker;
    std::shared_ptr<quite::probe::MouseInjector> mouse_injector;
    quite::proto::ProbeService::AsyncService object_service;

    QHooks::AddQObjectCallback next_add_qobject_hook_{nullptr};
    QHooks::RemoveQObjectCallback next_remove_qobject_hook_{nullptr};
    QHooks::StartupCallback next_startup_hook_{nullptr};

  private:
    std::jthread grpc_runner;
};

ProbeData &probeData()
{
    static ProbeData data{};
    return data;
}

void quite_add_object(QObject *q);
void quite_remove_object(QObject *q);
void quite_app_startup();

void installApplicationHooks()
{
    QObject::connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, []() { probeData().exit(); });
}

void installQHooks()
{
    Q_ASSERT(qtHookData[QHooks::HookDataVersion] >= 1);
    Q_ASSERT(qtHookData[QHooks::HookDataSize] >= 6);

    probeData().next_add_qobject_hook_ = reinterpret_cast<QHooks::AddQObjectCallback>(qtHookData[QHooks::AddQObject]);
    probeData().next_remove_qobject_hook_ =
        reinterpret_cast<QHooks::RemoveQObjectCallback>(qtHookData[QHooks::RemoveQObject]);
    probeData().next_startup_hook_ = reinterpret_cast<QHooks::StartupCallback>(qtHookData[QHooks::Startup]);

    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&quite_add_object);
    qtHookData[QHooks::RemoveQObject] = reinterpret_cast<quintptr>(&quite_remove_object);
    qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(&quite_app_startup);

    quite::probe::register_converters();
    if (QCoreApplication::instance() != nullptr)
    {
        installApplicationHooks();
    }
}

void quite_add_object(QObject *q)
{
    probeData().tracker->addObject(q);
    if (probeData().next_add_qobject_hook_ != nullptr)
    {
        probeData().next_add_qobject_hook_(q);
    }
}

void quite_remove_object(QObject *q)
{
    probeData().tracker->removeObject(q);
    if (probeData().next_remove_qobject_hook_ != nullptr)
    {
        probeData().next_remove_qobject_hook_(q);
    }
}

void quite_app_startup()
{
    installApplicationHooks();
    if (probeData().next_startup_hook_ != nullptr)
    {
        probeData().next_startup_hook_();
    }
}

} // namespace

namespace quite
{
void setupHooks()
{
    probeData(); // just create it at the beginnging
    installQHooks();
}
} // namespace quite
