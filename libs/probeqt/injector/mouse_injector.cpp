#include "mouse_injector.hpp"
#include <QCoreApplication>
#include <QPointer>

namespace quite::probe
{
MouseInjector::MouseInjector(const ObjectTracker &object_tracker)
    : object_tracker_{object_tracker}
    , mouse_{QStringLiteral("QuiteProbeTestingMouse"),
             100,
             QInputDevice::DeviceType::Mouse,
             QPointingDevice::PointerType::Generic,
             QInputDevice::Capability::MouseEmulation,
             1,
             3}
{}

MouseInjector::~MouseInjector() = default;

AsyncResult<void> MouseInjector::single_action(ObjectId target_id, core::MouseAction action)
{
    auto target = object_tracker_.get_object_by_id(target_id);
    if (not target.has_value())
    {
        co_return std::unexpected{target.error()};
    }
    std::unique_ptr<QMouseEvent> event;
    switch (action.trigger)
    {
    case core::MouseTrigger::none:
        break;
    case core::MouseTrigger::click:
        dispatch_mouse_event(target.value(),
                             std::make_unique<QMouseEvent>(QMouseEvent::Type::MouseButtonPress,
                                                           QPointF{action.position.x, action.position.y},
                                                           QPointF{},
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::KeyboardModifiers{},
                                                           &mouse_));
        dispatch_mouse_event(target.value(),
                             std::make_unique<QMouseEvent>(QMouseEvent::Type::MouseButtonRelease,
                                                           QPointF{action.position.x, action.position.y},
                                                           QPointF{},
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::KeyboardModifiers{},
                                                           &mouse_));
        break;
    case core::MouseTrigger::double_click:
        dispatch_mouse_event(target.value(),
                             std::make_unique<QMouseEvent>(QMouseEvent::Type::MouseButtonDblClick,
                                                           QPointF{action.position.x, action.position.y},
                                                           QPointF{},
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::KeyboardModifiers{},
                                                           &mouse_));
        break;
    case core::MouseTrigger::press:
        dispatch_mouse_event(target.value(),
                             std::make_unique<QMouseEvent>(QMouseEvent::Type::MouseButtonPress,
                                                           QPointF{action.position.x, action.position.y},
                                                           QPointF{},
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::KeyboardModifiers{},
                                                           &mouse_));
        break;
    case core::MouseTrigger::release:
        dispatch_mouse_event(target.value(),
                             std::make_unique<QMouseEvent>(QMouseEvent::Type::MouseButtonRelease,
                                                           QPointF{action.position.x, action.position.y},
                                                           QPointF{},
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::KeyboardModifiers{},
                                                           &mouse_));
        break;
    case core::MouseTrigger::move:
        dispatch_mouse_event(target.value(),
                             std::make_unique<QMouseEvent>(QMouseEvent::Type::MouseMove,
                                                           QPointF{action.position.x, action.position.y},
                                                           QPointF{},
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::MouseButton::LeftButton,
                                                           Qt::KeyboardModifiers{},
                                                           &mouse_));
        break;
    }

    if (event != nullptr)
    {
        QCoreApplication::postEvent(target.value(), event.release());
    }
    co_return {};
}

void MouseInjector::dispatch_mouse_event(QObject *target, std::unique_ptr<QMouseEvent> event)
{
    if (event != nullptr)
    {
        QCoreApplication::postEvent(target, event.release());
    }
}
} // namespace quite::probe
