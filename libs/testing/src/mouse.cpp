// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/test/mouse.hpp"
#include "quite/test/remote_object.hpp"

namespace quite::test
{

MouseBuilder::MouseBuilder(RemoteObject target)
    : target_{std::move(target)}
{}

MouseDragBuilder MouseDragBuilder::move_to(RemoteObject object)
{}

MouseDragBuilder MouseDragBuilder::drop_at(RemoteObject object)
{}

MouseBuilder MouseBuilder::up(MouseButton button)
{}

MouseBuilder MouseBuilder::down(MouseButton button)
{}

MouseBuilder MouseBuilder::modifier(KeyboardModifier modifier)
{
    modifiers_.set(modifier);
    return *this;
}

MouseDragBuilder MouseBuilder::drag(MouseButton button)
{}

MouseBuilder MouseBuilder::click(MouseButton button, std::chrono::milliseconds delay)
{}

MouseBuilder MouseBuilder::double_click(MouseButton button, std::chrono::milliseconds delay)
{}

MouseBuilder MouseBuilder::wheel(int delta_x, int delta_y)
{}

MouseBuilder mouse(RemoteObject target)
{
    return MouseBuilder{std::move(target)};
}
} // namespace quite::test
