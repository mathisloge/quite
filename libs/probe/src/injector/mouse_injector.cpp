#include "mouse_injector.hpp"
#include <QCoreApplication>
#include <QMouseEvent>

namespace quite::probe
{
MouseInjector::MouseInjector()
    : mouse_{QStringLiteral("TestingMouse"),
             100,
             QInputDevice::DeviceType::Mouse,
             QPointingDevice::PointerType::Generic,
             QInputDevice::Capability::MouseEmulation,
             1,
             2}
{}

MouseInjector::~MouseInjector() = default;

void MouseInjector::click_object(QObject *target, QPointF local_click_point)
{
    auto ev = new QMouseEvent(QMouseEvent::Type::MouseButtonPress,
                              local_click_point,
                              QPointF{0, 0},
                              Qt::MouseButton::LeftButton,
                              Qt::MouseButton::LeftButton,
                              {},
                              &mouse_);
    QCoreApplication::postEvent(target, std::move(ev));
    ev = new QMouseEvent(QMouseEvent::Type::MouseButtonRelease,
                         local_click_point,
                         QPointF{0, 0},
                         Qt::MouseButton::LeftButton,
                         Qt::MouseButton::LeftButton,
                         {},
                         &mouse_);
    QCoreApplication::postEvent(target, std::move(ev));
}
} // namespace quite::probe
