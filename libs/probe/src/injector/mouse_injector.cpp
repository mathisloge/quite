#include "mouse_injector.hpp"
#include <QCoreApplication>
#include <QMouseEvent>

namespace quite::probe
{
MouseInjector::MouseInjector(std::shared_ptr<ObjectTracker> object_tracker)
    : object_tracker_{object_tracker}
    , mouse_{QStringLiteral("TestingMouse"),
             100,
             QInputDevice::DeviceType::Mouse,
             QPointingDevice::PointerType::Generic,
             QInputDevice::Capability::MouseEmulation,
             1,
             3}
{}

MouseInjector::~MouseInjector() = default;

void MouseInjector::perform_action(ObjectId target_id,
                                   const proto::MouseButton &mouse_button,
                                   const proto::KeyboardModifierKey &mod_key,
                                   const proto::Vector2F &local_click_point)
{
    auto target_resp = object_tracker_->get_object_by_id(target_id);
    if (target_resp.has_value())
    {
        auto *target = target_resp.value();
        auto ev = new QMouseEvent(QMouseEvent::Type::MouseButtonPress,
                                  QPointF{local_click_point.x(), local_click_point.y()},
                                  QPointF{0, 0},
                                  Qt::MouseButton::LeftButton,
                                  Qt::MouseButton::LeftButton,
                                  {},
                                  &mouse_);
        QCoreApplication::postEvent(target, std::move(ev));
        ev = new QMouseEvent(QMouseEvent::Type::MouseButtonRelease,
                             QPointF{local_click_point.x(), local_click_point.y()},
                             QPointF{0, 0},
                             Qt::MouseButton::LeftButton,
                             Qt::MouseButton::LeftButton,
                             {},
                             &mouse_);
        QCoreApplication::postEvent(target, std::move(ev));
    };
}
} // namespace quite::probe
