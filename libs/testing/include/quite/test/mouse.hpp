// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <chrono>
#include <quite/core/bit_flags.hpp>
#include <quite/keyboard.hpp>
#include <quite/mouse.hpp>
#include "quite/quite_test_export.hpp"
#include "quite/test/remote_object.hpp"

namespace quite::test
{
class QUITE_TEST_EXPORT MouseDragBuilder
{
    MouseDragBuilder move_to(RemoteObject object);
    MouseDragBuilder drop_at(RemoteObject object);

  private:
    RemoteObject source_;
};

class QUITE_TEST_EXPORT MouseBuilder
{
  public:
    MouseBuilder() = delete;
    MouseBuilder(const MouseBuilder &other) = default;
    MouseBuilder(MouseBuilder &&other) noexcept = default;
    MouseBuilder &operator=(const MouseBuilder &other) = default;
    MouseBuilder &operator=(MouseBuilder &&other) = default;
    ~MouseBuilder() = default;

    MouseBuilder up(MouseButton button);
    MouseBuilder down(MouseButton button);
    MouseBuilder modifier(KeyboardModifier modifier);
    MouseDragBuilder drag(MouseButton button = MouseButton::left);
    MouseBuilder click(MouseButton button = MouseButton::left,
                       std::chrono::milliseconds delay = std::chrono::milliseconds{0});
    MouseBuilder double_click(MouseButton button = MouseButton::left,
                              std::chrono::milliseconds delay = std::chrono::milliseconds{0});
    MouseBuilder wheel(int delta_x, int delta_y);

  private:
    MouseBuilder(RemoteObject target);
    friend MouseBuilder mouse(RemoteObject target);

  private:
    RemoteObject target_;
    BitFlags<KeyboardModifier> modifiers_;
};

[[nodiscard]] QUITE_TEST_EXPORT MouseBuilder mouse(RemoteObject target);
} // namespace quite::test
