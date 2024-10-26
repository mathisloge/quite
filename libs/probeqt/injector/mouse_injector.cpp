#include "mouse_injector.hpp"
#include <QCoreApplication>
#include <QMouseEvent>

namespace quite::probe
{
MouseInjector::MouseInjector(ObjectTracker &object_tracker)
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

void MouseInjector::perform_action(ObjectId target_id,
                                   const proto::MouseAction &action,
                                   const proto::MouseButton &button,
                                   const proto::KeyboardModifierKey &mod_key,
                                   const proto::Vector2F &local_target_point)
{
    auto target_resp = object_tracker_.get_object_by_id(target_id);
    if (target_resp.has_value())
    {
        auto *target = target_resp.value();
        switch (action)
        {
        case proto::click:
            dispatchMouseEvent(target, QMouseEvent::Type::MouseButtonPress, button, mod_key, local_target_point);
            dispatchMouseEvent(target, QMouseEvent::Type::MouseButtonRelease, button, mod_key, local_target_point);
            break;
        case proto::double_click:
            dispatchMouseEvent(target, QMouseEvent::Type::MouseButtonDblClick, button, mod_key, local_target_point);
            break;
        case proto::press:
            dispatchMouseEvent(target, QMouseEvent::Type::MouseButtonPress, button, mod_key, local_target_point);
            break;
        case proto::release:
            dispatchMouseEvent(target, QMouseEvent::Type::MouseButtonRelease, button, mod_key, local_target_point);
            break;
        case proto::move:
            dispatchMouseEvent(target, QMouseEvent::Type::MouseMove, button, mod_key, local_target_point);
            break;
        case proto::none:
        case proto::MouseAction_INT_MIN_SENTINEL_DO_NOT_USE_:
        case proto::MouseAction_INT_MAX_SENTINEL_DO_NOT_USE_:
            break;
        }
    };
}

void MouseInjector::dispatchMouseEvent(QObject *target,
                                       QMouseEvent::Type event,
                                       const proto::MouseButton &button,
                                       const proto::KeyboardModifierKey &mod_key,
                                       const proto::Vector2F &local_target_point)
{
    auto ev = new QMouseEvent(event,
                              QPointF{local_target_point.x(), local_target_point.y()},
                              QPointF{0, 0},
                              Qt::MouseButton::LeftButton,
                              Qt::MouseButton::LeftButton,
                              {},
                              &mouse_);
    QCoreApplication::postEvent(target, std::move(ev));
}
} // namespace quite::probe
