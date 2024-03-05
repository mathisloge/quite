#include "quite/probe.hpp"
#include <iostream>
#include <thread>
#include <QtCore/private/qhooks_p.h>
#include <agrpc/asio_grpc.hpp>
#include <fmt/compile.h>
#include <fmt/format.h>
#include <grpcpp/server_builder.h>
#include <quite/object_service.hpp>
#include "object_tracker.hpp"

namespace
{

class ProbeObjectService final : public quite::ObjectService
{
  public:
    using ObjectService::ObjectService;

    void onSayHello(const quite::proto::HelloRequest &request, quite::proto::HelloReply &response) override
    {
        *response.mutable_message() = fmt::format(FMT_COMPILE("{} <3 from probe"), request.name());
    }
};
struct ProbeData final
{
    ProbeData(grpc::ServerBuilder builder)
        : grpc_context{builder.AddCompletionQueue()}
        , object_service{grpc_context, builder}
    {
        builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
        server = builder.BuildAndStart();

        grpc_runner = std::jthread{[this]() { grpc_context.run(); }};
    }

    agrpc::GrpcContext grpc_context;
    std::unique_ptr<grpc::Server> server;
    ProbeObjectService object_service;
    quite::ObjectTracker tracker;

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
    std::cout << "startup" << std::endl;
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
