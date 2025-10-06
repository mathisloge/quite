// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <chrono>
#include <quite/keyboard.hpp>
#include <quite/mouse.hpp>
#include "quite/quite_test_export.hpp"
namespace quite::test
{
class RemoteObject;

class MouseDragBuilder
{
    MouseDragBuilder move_to(RemoteObject object);
    MouseDragBuilder drop_at(RemoteObject object);
};

class MouseBuilder
{
    MouseBuilder up(MouseButton button);
    MouseBuilder down(MouseButton button);
    MouseBuilder modifier(KeyboardModifier modifier);
    MouseDragBuilder drag(MouseButton button = MouseButton::left);
    MouseBuilder click(MouseButton button = MouseButton::left,
                       std::chrono::milliseconds delay = std::chrono::milliseconds{0});
    MouseBuilder double_click(MouseButton button = MouseButton::left,
                              std::chrono::milliseconds delay = std::chrono::milliseconds{0});
    MouseBuilder wheel(int delta_x, int delta_y);
};

[[nodiscard]] QUITE_TEST_EXPORT MouseBuilder mouse(RemoteObject object);
} // namespace quite::test
