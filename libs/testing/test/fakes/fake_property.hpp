// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <deque>
#include <quite/client/property.hpp>

namespace quite::test::fakes
{
// Returns the next value from a fixed sequence on each read(), repeating the last one once
// exhausted; used to drive Property::wait_for_value's polling loop deterministically.
class FakeProperty final : public client::Property
{
  public:
    // NOTE: uses parens, not braces, for the member-initializers below. entt::meta_any's
    // catch-all templated constructor makes std::deque<entt::meta_any> convertible to
    // entt::meta_any itself, so brace-init would prefer deque's initializer_list constructor
    // over its move constructor and wrap the whole sequence as a single element.
    explicit FakeProperty(std::deque<entt::meta_any> read_sequence)
        : read_sequence_(std::move(read_sequence))
        , last_value_(read_sequence_.front())
    {}

    const std::string &name() const override
    {
        static const std::string kName = "fake";
        return kName;
    }

    meta::TypeId type_id() const override
    {
        return 0;
    }

    const Result<entt::meta_any> &value() const override
    {
        return last_value_;
    }

    AsyncResult<entt::meta_any> read() override
    {
        if (read_sequence_.size() > 1)
        {
            read_sequence_.pop_front();
        }
        last_value_ = read_sequence_.front();
        co_return last_value_;
    }

    AsyncResult<void> write(entt::meta_any value) override
    {
        last_value_ = std::move(value);
        co_return Result<void>{};
    }

  private:
    std::deque<entt::meta_any> read_sequence_;
    Result<entt::meta_any> last_value_;
};
} // namespace quite::test::fakes
