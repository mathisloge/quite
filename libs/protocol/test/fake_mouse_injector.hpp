// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <optional>
#include <quite/injectors/mouse_injector.hpp>

namespace quite::proto::test
{
// Records the last single_action() call so a round-trip test can assert the proto request was
// decoded correctly server-side (rpc_mouse_injection.cpp's enum mapping in particular).
class FakeMouseInjector final : public core::IMouseInjector
{
  public:
    struct Call
    {
        ObjectId target_id;
        core::MouseAction action;
    };

    const std::optional<Call> &last_call() const
    {
        return last_call_;
    }

    AsyncResult<void> single_action(ObjectId target_id, core::MouseAction action) override
    {
        last_call_ = Call{.target_id = target_id, .action = action};
        co_return Result<void>{};
    }

  private:
    std::optional<Call> last_call_;
};
} // namespace quite::proto::test
