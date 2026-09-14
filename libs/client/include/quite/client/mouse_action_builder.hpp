// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/injectors/mouse_injector.hpp>
#include "quite/client/remote_object.hpp"
#include "quite/quite_client_export.hpp"

namespace quite::client
{
class QUITE_CLIENT_EXPORT MouseActionBuilder
{
  public:
    MouseActionBuilder modifier(KeyboardModifier modifier);
    AsyncResult<MouseActionBuilder> click(MouseButton button = MouseButton::left);
    AsyncResult<MouseActionBuilder> double_click(MouseButton button = MouseButton::left,
                                                 std::chrono::milliseconds delay = std::chrono::milliseconds{10});

    AsyncResult<MouseActionBuilder> wheel(int delta_x, int delta_y);

    /**
    button=none => hover
    */
    AsyncResult<MouseActionBuilder> move_to(RemoteObjectPtr new_target, MouseButton button = MouseButton::none);

  private:
    RemoteObjectPtr target_;
    MouseEventOptions options_{};
};

MouseActionBuilder mouse(RemoteObjectPtr target);
} // namespace quite::client
