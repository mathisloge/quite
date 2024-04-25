#include "quite/probe.hpp"
#include <thread>
#include <QtCore/private/qhooks_p.h>
#include <agrpc/asio_grpc.hpp>
#include <asio/compose.hpp>
#include <fmt/compile.h>
#include <fmt/format.h>
#include <grpcpp/server_builder.h>
#include <quite/object_service.hpp>
#include <spdlog/spdlog.h>
#include "asio_event.hpp"
#include "object_tracker.hpp"
#include "property_collector.hpp"
namespace
{
// see https://cppalliance.org/richard/2020/10/31/RichardsOctoberUpdate.html
// https://github.com/madmongo1/blog-october-2020/blob/stage-2/src/qt_net_application.cpp
struct async_find_object_implementation
{
    template <typename Self>
    void operator()(Self &self, asio::error_code error = {}, std::size_t n = 0)
    {
        self.complete();
    }
};

template <typename CompletionToken>
auto async_find_object(CompletionToken &&token) ->
    typename asio::async_result<typename std::decay<CompletionToken>::type,
                                void(asio::error_code, std::size_t)>::return_type
{
    // create the request QObject, which binds to the object tracker track signal.
    // as soon as the object is found, the implementations complete should be called, (e.g. when calling the
    // find_object, )
    return asio::async_compose<CompletionToken, void(asio::error_code, std::size_t)>(
        async_find_object_implementation{}, token, socket);
}

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
        *response.mutable_message() = fmt::format(FMT_COMPILE("{} <3 from probe"), request.name());
    }

    void onFindObject(const quite::proto::ObjectRequest &request, quite::proto::ObjectReply &response) override
    {
        spdlog::error("start find obj with name {}", request.object_name());
        // todo: this must be done on the qt thread.
        // async_find_object?
        auto props = object_tracker_.findObject(request.object_name());
        // response.mutable_properties()->insert(props.begin(), props.end());
    }

  private:
    quite::ObjectTracker &object_tracker_;
};

class AsioEventHandler : public QObject
{
    Q_OBJECT
  public:
    using QObject::QObject;

  protected:
    bool event(QEvent *event) override
    {
        using namespace quite::probe;
        if (event->type() == qt_work_event_base::generated_type())
        {
            auto p = static_cast<qt_work_event_base *>(event);
            p->accept();
            p->invoke();
            return true;
        }
        return QObject::event(event);
    }
};
struct ProbeData final
{
    ProbeData(grpc::ServerBuilder builder)
        : grpc_context{builder.AddCompletionQueue()}
        , object_service{grpc_context, builder, tracker}
    {
        builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
        server = builder.BuildAndStart();

        grpc_runner = std::jthread{[this]() { grpc_context.run(); }};
    }
    AsioEventHandler event_handler_;
    agrpc::GrpcContext grpc_context;
    std::unique_ptr<grpc::Server> server;
    quite::ObjectTracker tracker;
    ProbeObjectService object_service;

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

#include "probe.moc"
