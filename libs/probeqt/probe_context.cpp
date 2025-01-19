#include "probe_context.hpp"
#include <QCoreApplication>
#include <csignal>
#include <entt/locator/locator.hpp>
#include <exec/finally.hpp>
#include <quite/logger.hpp>
#include "rpc/create_snapshot.hpp"
#include "rpc/exit_request.hpp"
#include "rpc/find_object.hpp"
#include "rpc/get_object_properties.hpp"
#include "rpc/get_views.hpp"
#include "rpc/invoke_method.hpp"
#include "rpc/meta_find_type.hpp"
#include "rpc/mouse_action.hpp"
#include "value_converters.hpp"

DEFINE_LOGGER(probe_ctx_logger)

namespace quite::probe
{

namespace
{
void quite_add_object(QObject *q);
void quite_remove_object(QObject *q);
void quite_app_startup();
} // namespace

ProbeContext::ProbeContext(grpc::ServerBuilder builder)
    : grpc_context_{builder.AddCompletionQueue()}
    , mouse_injector_{object_tracker_}
    , method_invoker_{object_tracker_}
{
    builder.RegisterService(std::addressof(object_service_));
    builder.RegisterService(std::addressof(meta_service_));
    builder.AddListeningPort("unix:///tmp/grpc_probe.sock", grpc::InsecureServerCredentials());
    grpc_server_ = builder.BuildAndStart();

    grpc_runner_ = std::jthread{[this]() {
        auto find_obj_rpc = quite::probe::find_object(grpc_context_, object_service_, object_tracker_);
        auto get_object_properties_rpc =
            quite::probe::get_object_properties(grpc_context_, object_service_, object_tracker_);
        auto mouse_action_rpc = quite::probe::mouse_action(grpc_context_, object_service_, mouse_injector_);
        auto create_snapshot_rpc = quite::probe::create_snapshot(grpc_context_, object_service_, object_tracker_);
        auto get_views_rpc = quite::probe::get_views(grpc_context_, object_service_, object_tracker_);
        auto exit_request_rpc = quite::probe::exit_request(grpc_context_, object_service_);
        auto invoke_method_rpc =
            quite::probe::invoke_method(grpc_context_, object_service_, object_tracker_, method_invoker_);

        auto meta_find_type_rpc = quite::probe::meta_find_type(grpc_context_, meta_service_, meta_adapter_);
        LOG_INFO(probe_ctx_logger, "grpc server setup and is now running.");
        grpc_context_.work_started();
        auto snd = exec::finally(stdexec::when_all( //
                                     std::move(find_obj_rpc),
                                     std::move(get_object_properties_rpc),
                                     std::move(mouse_action_rpc),
                                     std::move(create_snapshot_rpc),
                                     std::move(get_views_rpc),
                                     std::move(exit_request_rpc),
                                     std::move(invoke_method_rpc),
                                     std::move(meta_find_type_rpc)),
                                 stdexec::then(stdexec::just(), [this] { grpc_context_.work_finished(); }));
        stdexec::sync_wait(
            stdexec::when_all(std::move(snd), stdexec::then(stdexec::just(), [this] { grpc_context_.run(); })));
        LOG_INFO(probe_ctx_logger, "grpc server is now finished. Closing the connection.");
    }};
    install_qt_hooks();
}

ProbeContext::~ProbeContext()
{
    request_exit();
}

void ProbeContext::request_exit()
{
    LOG_INFO(probe_ctx_logger, "requested probe exit. Grpc server is now is shutdown.");
    grpc_server_->Shutdown(std::chrono::system_clock::now() + std::chrono::seconds{2});
    grpc_server_->Wait();
    grpc_context_.stop();
}

void ProbeContext::install_qt_hooks()
{
    Q_ASSERT(qtHookData[QHooks::HookDataVersion] >= 1);
    Q_ASSERT(qtHookData[QHooks::HookDataSize] >= 6);

    const auto qt_version_number = qtHookData[QHooks::QtVersion];
    const auto qt_major = (qt_version_number >> 16) & 0xFF;
    const auto qt_minor = (qt_version_number >> 8) & 0xFF;
    const auto qt_patch = qt_version_number & 0xFF;

    LOG_INFO(probe_ctx_logger, "installing Qt hooks for Qt version {}.{}.{}", qt_major, qt_minor, qt_patch);

    next_add_qobject_hook_ = reinterpret_cast<QHooks::AddQObjectCallback>(qtHookData[QHooks::AddQObject]);
    next_remove_qobject_hook_ = reinterpret_cast<QHooks::RemoveQObjectCallback>(qtHookData[QHooks::RemoveQObject]);
    next_startup_hook_ = reinterpret_cast<QHooks::StartupCallback>(qtHookData[QHooks::Startup]);

    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&quite_add_object);
    qtHookData[QHooks::RemoveQObject] = reinterpret_cast<quintptr>(&quite_remove_object);
    qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(&quite_app_startup);

    quite::probe::register_converters();
    if (QCoreApplication::instance() != nullptr)
    {
        install_application_hooks();
    }
}

void ProbeContext::install_application_hooks()
{
    LOG_INFO(probe_ctx_logger, "installing QCoreApplication signals...");
    QObject::connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, [this]() { request_exit(); });
}

void ProbeContext::qt_hook_add_object(QObject *q)
{
    object_tracker_.add_object(q);
    if (next_add_qobject_hook_ != nullptr)
    {
        next_add_qobject_hook_(q);
    }
}

void ProbeContext::qt_hook_remove_object(QObject *q)
{
    object_tracker_.remove_object(q);
    if (next_remove_qobject_hook_ != nullptr)
    {
        next_remove_qobject_hook_(q);
    }
}

void ProbeContext::qt_hook_startup()
{
    install_application_hooks();
    if (next_startup_hook_ != nullptr)
    {
        next_startup_hook_();
    }
}

namespace
{
void quite_add_object(QObject *q)
{
    auto &&probe_context_handle = entt::locator<ProbeContext>::value();
    probe_context_handle.qt_hook_add_object(q);
}

void quite_remove_object(QObject *q)
{
    auto &&probe_context_handle = entt::locator<ProbeContext>::value();
    probe_context_handle.qt_hook_remove_object(q);
}

void quite_app_startup()
{
    auto &&probe_context_handle = entt::locator<ProbeContext>::value();
    probe_context_handle.qt_hook_startup();
}
} // namespace

} // namespace quite::probe
