// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/client/mouse_action_builder.hpp"
#include "quite/client/probe_context.hpp"

namespace quite::client
{
MouseActionBuilder MouseActionBuilder::modifier(KeyboardModifier modifier)
{
    options_.modifiers.set(modifier);
    return *this;
}

AsyncResult<MouseActionBuilder> MouseActionBuilder::click(MouseButton button)
{
    if (not target_)
    {
        co_return make_error_result(ErrorCode::failed_precondition, "Mouse target is missing.");
    }
    const auto state = co_await target_->probe_context()->mouse_injector().perfom_on_target(
        target_->id(), MouseTrigger::click, button, options_);
    if (not state)
    {
        co_return std::unexpected(state.error());
    }
    co_return *this;
}

AsyncResult<MouseActionBuilder> MouseActionBuilder::double_click(MouseButton button, std::chrono::milliseconds delay)
{
    co_return make_error_result(ErrorCode::unimplemented, "Not yet implemented");
}

AsyncResult<MouseActionBuilder> MouseActionBuilder::wheel(int delta_x, int delta_y)
{
    co_return make_error_result(ErrorCode::unimplemented, "Not yet implemented");
}

AsyncResult<MouseActionBuilder> MouseActionBuilder::move_to(RemoteObjectPtr new_target, MouseButton button)
{
    if (new_target == nullptr)
    {
        co_return make_error_result(ErrorCode::failed_precondition, "Mouse target is missing.");
    }
    target_ = std::move(new_target);
    const auto state = co_await target_->probe_context()->mouse_injector().perfom_on_target(
        target_->id(), MouseTrigger::move, button, options_);
    if (not state)
    {
        co_return std::unexpected(state.error());
    }
    co_return *this;
}
} // namespace quite::client
