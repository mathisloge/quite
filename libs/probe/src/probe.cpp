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
#include "rpc/find_object_rpc.hpp"
#include "rpc/get_object_property.hpp"
#include "rpc/mouse_click.hpp"
namespace
{

using RpcFindObjectSender = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;

struct ProbeData final
{
    ProbeData(grpc::ServerBuilder builder)
        : grpc_context{builder.AddCompletionQueue()}
        , tracker{std::make_shared<quite::ObjectTracker>()}
        , mouse_injector{std::make_shared<quite::probe::MouseInjector>(tracker)}
    {
        using namespace quite;
        builder.RegisterService(&object_service);
        builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
        server = builder.BuildAndStart();

        grpc_runner = std::jthread{[this]() {
            auto find_obj_rpc = quite::probe::find_object_rpc(grpc_context, object_service, *tracker);
            auto get_object_property = quite::probe::get_object_property(grpc_context, object_service, *tracker);
            auto mouse_click_rpc = quite::probe::mouse_click(grpc_context, object_service, *mouse_injector);
            auto create_snapshot_rpc = quite::probe::create_snapshot(grpc_context, object_service, *tracker);

            grpc_context.work_started();
            auto snd = exec::finally(
                stdexec::when_all(find_obj_rpc, get_object_property, mouse_click_rpc, create_snapshot_rpc),
                stdexec::then(stdexec::just(), [this] { grpc_context.work_finished(); }));
            stdexec::sync_wait(
                stdexec::when_all(std::move(snd), stdexec::then(stdexec::just(), [&] { grpc_context.run(); })));
            spdlog::error("CLOSING GRPC");
        }};
    }

    agrpc::GrpcContext grpc_context;
    std::unique_ptr<grpc::Server> server;
    std::shared_ptr<quite::ObjectTracker> tracker;
    std::shared_ptr<quite::probe::MouseInjector> mouse_injector;
    quite::proto::ProbeService::AsyncService object_service;

  private:
    std::jthread grpc_runner;
};

ProbeData &probeData()
{
    static ProbeData data{{}};
    return data;
}

void testAddObject(QObject *q);
void testRemoveObject(QObject *q);
void testStartup();

void installQHooks()
{
    Q_ASSERT(qtHookData[QHooks::HookDataVersion] >= 1);
    Q_ASSERT(qtHookData[QHooks::HookDataSize] >= 6);

    // gammaray_next_addObject =
    // reinterpret_cast<QHooks::AddQObjectCallback>(qtHookData[QHooks::AddQObject]);
    // gammaray_next_removeObject =
    // reinterpret_cast<QHooks::RemoveQObjectCallback>(qtHookData[QHooks::RemoveQObject]);
    // gammaray_next_startup_hook =
    // reinterpret_cast<QHooks::StartupCallback>(qtHookData[QHooks::Startup]);

    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&testAddObject);
    qtHookData[QHooks::RemoveQObject] = reinterpret_cast<quintptr>(&testRemoveObject);
    qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(&testStartup);
}

void testAddObject(QObject *q)
{
    probeData().tracker->addObject(q);
}

void testRemoveObject(QObject *q)
{
    probeData().tracker->removeObject(q);
}

void testStartup()
{
    spdlog::set_level(spdlog::level::debug);
}

} // namespace

namespace quite
{
void setupHooks()
{
    probeData();
    installQHooks();
}
} // namespace quite
