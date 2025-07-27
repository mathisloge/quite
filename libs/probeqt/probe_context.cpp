#include "probe_context.hpp"
#include <QCoreApplication>
#include <csignal>
#include <entt/locator/locator.hpp>
#include <quite/logger.hpp>
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

ProbeContext::ProbeContext(std::string server_address)
    : server_{std::move(server_address), probe_handler_, mouse_injector_, meta_registry_, value_registry_}
{
    quite::probe::register_converters(*value_registry_);
    install_qt_hooks();
}

ProbeContext::~ProbeContext()
{
    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(next_add_qobject_hook_);
    qtHookData[QHooks::RemoveQObject] = reinterpret_cast<quintptr>(next_remove_qobject_hook_);
    qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(next_startup_hook_);
}

void ProbeContext::install_qt_hooks()
{
    Q_ASSERT(qtHookData[QHooks::HookDataVersion] >= 1);
    Q_ASSERT(qtHookData[QHooks::HookDataSize] >= 6);

    const auto qt_version_number = qtHookData[QHooks::QtVersion];
    const auto qt_major = (qt_version_number >> 16) & 0xFF;
    const auto qt_minor = (qt_version_number >> 8) & 0xFF;
    const auto qt_patch = qt_version_number & 0xFF;

    LOG_INFO(probe_ctx_logger(), "Installing Qt hooks for Qt version {}.{}.{}", qt_major, qt_minor, qt_patch);

    next_add_qobject_hook_ = reinterpret_cast<QHooks::AddQObjectCallback>(qtHookData[QHooks::AddQObject]);
    next_remove_qobject_hook_ = reinterpret_cast<QHooks::RemoveQObjectCallback>(qtHookData[QHooks::RemoveQObject]);
    next_startup_hook_ = reinterpret_cast<QHooks::StartupCallback>(qtHookData[QHooks::Startup]);

    qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&quite_add_object);
    qtHookData[QHooks::RemoveQObject] = reinterpret_cast<quintptr>(&quite_remove_object);
    qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(&quite_app_startup);

    if (QCoreApplication::instance() != nullptr)
    {
        install_application_hooks();
    }
}

void ProbeContext::install_application_hooks()
{
    LOG_INFO(probe_ctx_logger(), "installing QCoreApplication signals...");
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
