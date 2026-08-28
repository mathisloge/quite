// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "mouse_injector.hpp"
#include <QCoreApplication>
#include <QPointer>

namespace
{
Qt::MouseButton to_qt_button(quite::core::MouseButton button)
{
    switch (button)
    {
    case quite::core::MouseButton::none:
        return Qt::NoButton;
    case quite::core::MouseButton::left:
        return Qt::LeftButton;
    case quite::core::MouseButton::right:
        return Qt::RightButton;
    case quite::core::MouseButton::middle:
        return Qt::MiddleButton;
    case quite::core::MouseButton::forward:
        return Qt::ForwardButton;
    case quite::core::MouseButton::back:
        return Qt::BackButton;
    }
    return Qt::NoButton;
}

Qt::KeyboardModifiers to_qt_modifiers(quite::core::KeyboardModifier modifier)
{
    switch (modifier)
    {
    case quite::core::KeyboardModifier::none:
        return Qt::NoModifier;
    case quite::core::KeyboardModifier::shift:
        return Qt::ShiftModifier;
    case quite::core::KeyboardModifier::control:
        return Qt::ControlModifier;
    case quite::core::KeyboardModifier::alt:
        return Qt::AltModifier;
    case quite::core::KeyboardModifier::meta:
        return Qt::MetaModifier;
    }
    return Qt::NoModifier;
}
} // namespace

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

    const QPointF position{action.position.x, action.position.y};
    const Qt::MouseButton button = to_qt_button(action.button);
    const Qt::KeyboardModifiers modifiers = to_qt_modifiers(action.modifier);

    switch (action.trigger)
    {
    case core::MouseTrigger::none:
        break;
    case core::MouseTrigger::click:
        dispatch_mouse_event(
            target.value(),
            std::make_unique<QMouseEvent>(
                QMouseEvent::Type::MouseButtonPress, position, QPointF{}, button, button, modifiers, &mouse_));
        dispatch_mouse_event(
            target.value(),
            std::make_unique<QMouseEvent>(
                QMouseEvent::Type::MouseButtonRelease, position, QPointF{}, button, button, modifiers, &mouse_));
        break;
    case core::MouseTrigger::double_click:
        dispatch_mouse_event(
            target.value(),
            std::make_unique<QMouseEvent>(
                QMouseEvent::Type::MouseButtonDblClick, position, QPointF{}, button, button, modifiers, &mouse_));
        break;
    case core::MouseTrigger::press:
        dispatch_mouse_event(
            target.value(),
            std::make_unique<QMouseEvent>(
                QMouseEvent::Type::MouseButtonPress, position, QPointF{}, button, button, modifiers, &mouse_));
        break;
    case core::MouseTrigger::release:
        dispatch_mouse_event(
            target.value(),
            std::make_unique<QMouseEvent>(
                QMouseEvent::Type::MouseButtonRelease, position, QPointF{}, button, button, modifiers, &mouse_));
        break;
    case core::MouseTrigger::move:
        dispatch_mouse_event(
            target.value(),
            std::make_unique<QMouseEvent>(
                QMouseEvent::Type::MouseMove, position, QPointF{}, button, button, modifiers, &mouse_));
        break;
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
