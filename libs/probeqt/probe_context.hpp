#pragma once
#include <private/qhooks_p.h>
#include <quite/disable_copy_move.hpp>
#include <quite/proto/probe/server.hpp>
#include "object_tracker.hpp"
#include "probe_instances.hpp"

namespace quite::probe
{
class ProbeContext final
{
  public:
    QUITE_DISABLE_COPY_MOVE(ProbeContext);
    explicit ProbeContext(std::string server_address);
    ~ProbeContext();

    void qt_hook_add_object(QObject *q);
    void qt_hook_remove_object(QObject *q);
    void qt_hook_startup();

  private:
    void install_qt_hooks();
    void install_application_hooks();

  private:
    quite::probe::ObjectTracker object_tracker_;
    ProbeInstances instances_{object_tracker_};
    quite::proto::Server server_;

    QHooks::AddQObjectCallback next_add_qobject_hook_{nullptr};
    QHooks::RemoveQObjectCallback next_remove_qobject_hook_{nullptr};
    QHooks::StartupCallback next_startup_hook_{nullptr};
};
} // namespace quite::probe
