

# File probe\_context.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**probe\_context.hpp**](probe__context_8hpp.md)

[Go to the documentation of this file](probe__context_8hpp.md)


```C++
#pragma once
#include <private/qhooks_p.h>
#include <quite/disable_copy_move.hpp>
#include <quite/proto/probe/server.hpp>
#include "injector/mouse_injector.hpp"
#include "object_tracker.hpp"
#include "qt_meta_registry.hpp"
#include "qt_probe_handler.hpp"

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
    ServiceHandle<proto::IProbeHandler> probe_handler_{std::make_shared<QtProbeHandler>(object_tracker_)};
    ServiceHandle<core::IMouseInjector> mouse_injector_{std::make_shared<MouseInjector>(object_tracker_)};
    ServiceHandle<meta::MetaRegistry> meta_registry_{std::make_shared<QtMetaRegistry>()};
    ServiceHandle<ValueRegistry> value_registry_{std::in_place};
    quite::proto::Server server_;

    QHooks::AddQObjectCallback next_add_qobject_hook_{nullptr};
    QHooks::RemoveQObjectCallback next_remove_qobject_hook_{nullptr};
    QHooks::StartupCallback next_startup_hook_{nullptr};
};
} // namespace quite::probe
```


