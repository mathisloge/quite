

# File mouse\_injector.hpp

[**File List**](files.md) **>** [**injector**](dir_91fe3d89382dfb9ec1070f72fd853fa0.md) **>** [**mouse\_injector.hpp**](probeqt_2injector_2mouse__injector_8hpp.md)

[Go to the documentation of this file](probeqt_2injector_2mouse__injector_8hpp.md)


```C++
#pragma once
#include <QMouseEvent>
#include <QPointingDevice>
#include <quite/injectors/mouse_injector.hpp>
#include <quite/value/object_id.hpp>
#include "object_tracker.hpp"
namespace quite::probe
{

class MouseInjector final : public core::IMouseInjector
{
  public:
    explicit MouseInjector(const ObjectTracker &object_tracker);
    ~MouseInjector() override;

    AsyncResult<void> single_action(ObjectId target_id, core::MouseAction action) override;

  private:
    static void dispatch_mouse_event(QObject *target, std::unique_ptr<QMouseEvent> event);

  private:
    const ObjectTracker &object_tracker_;
    QPointingDevice mouse_;
};
} // namespace quite::probe
```


