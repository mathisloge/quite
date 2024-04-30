#include "quite/probe.hpp"
#include <QCoreApplication>
#include <thread>
#include <QtCore/private/qhooks_p.h>
#include <agrpc/asio_grpc.hpp>
#include <asio/compose.hpp>
#include <exec/finally.hpp>
#include <exec/inline_scheduler.hpp>
#include <exec/static_thread_pool.hpp>
#include <exec/task.hpp>
#include <fmt/compile.h>
#include <fmt/format.h>
#include <grpcpp/server_builder.h>
#include <object/object.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "object_tracker.hpp"
#include "property_collector.hpp"
#include "qtstdexec.h"
namespace
{

/*
class ProbeObjectService final : public quite::ObjectService
{
  public:
    explicit ProbeObjectService(agrpc::GrpcContext &context,
                                grpc::ServerBuilder &builder,
                                quite::ObjectTracker &object_tracker)
        : ObjectService{context, builder}
        , object_tracker_{object_tracker}
    {}

    void onSayHello(const quite::proto::HelloRequest &request, quite::proto::HelloReply &response) override
    {
        // QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread()) | stdexec::then([this](){});
        *response.mutable_message() = fmt::format(FMT_COMPILE("{} <3 from probe"), request.name());
    }

    exec::task<void> onFindObject(const quite::proto::ObjectRequest &request,
                                  quite::proto::ObjectReply &response) override
    {

        spdlog::error("start find obj with name {}", request.object_name());
        co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                               [this, &request, &response]() {
                                   auto props = object_tracker_.findObject(request.object_name());
                                   response.mutable_properties()->insert(props.begin(), props.end());
                               });
        spdlog::error("end find obj with name {}", request.object_name());
        // todo: this must be done on the qt thread.
        // async_find_object?
        // auto props = object_tracker_.findObject(request.object_name());
        // response.mutable_properties()->insert(props.begin(), props.end());
    }

  private:
    quite::ObjectTracker &object_tracker_;
};
*/
using RpcFindObjectSender = agrpc::ServerRPC<&quite::proto::ObjectService::AsyncService::RequestFindObject>;

struct ProbeData final
{
    ProbeData(grpc::ServerBuilder builder)
        : grpc_context{builder.AddCompletionQueue()}
    {
        builder.RegisterService(&object_service);
        builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
        server = builder.BuildAndStart();

        grpc_runner = std::jthread{[this]() {
            auto find_obj = agrpc::register_sender_rpc_handler<RpcFindObjectSender>(
                grpc_context,
                object_service,
                [this](RpcFindObjectSender &rpc, const RpcFindObjectSender::Request &request) -> exec::task<void> {
                    spdlog::error("GOT FIND REQUEST");
                    RpcFindObjectSender::Response response{};
                    co_await stdexec::then(
                        stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                        [&, this]() {
                            auto props = tracker.findObject(request.object_name());
                            spdlog::debug("GOT PROPS={}", props.size());
                            props.emplace("test", "prop");
                            response.mutable_properties()->insert(props.begin(), props.end());
                        });
                    spdlog::error("finished");
                    co_await rpc.finish(response, grpc::Status::OK);
                });
            spdlog::error("Start work");
            grpc_context.work_started();
            auto snd = exec::finally(stdexec::when_all(find_obj), stdexec::then(stdexec::just(), [this] {
                                         spdlog::debug("grpc finished");
                                         grpc_context.work_finished();
                                     }));
            stdexec::sync_wait(stdexec::when_all(snd, stdexec::then(stdexec::just(), [&] { grpc_context.run(); })));
            spdlog::error("ending!!!!!");
        }};
    }

    agrpc::GrpcContext grpc_context;
    std::unique_ptr<grpc::Server> server;
    quite::ObjectTracker tracker;
    quite::proto::ObjectService::AsyncService object_service;
    // ProbeObjectService object_service;

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
    probeData().tracker.addObject(q);
}

void testRemoveObject(QObject *q)
{
    probeData().tracker.removeObject(q);
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
