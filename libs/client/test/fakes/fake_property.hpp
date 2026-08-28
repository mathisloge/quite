// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/client/property.hpp>

namespace quite::client::test
{
class FakeProperty final : public Property
{
  public:
    FakeProperty(std::string name, Result<entt::meta_any> value)
        : name_{std::move(name)}
        , value_{std::move(value)}
    {}

    const std::string &name() const override
    {
        return name_;
    }

    meta::TypeId type_id() const override
    {
        return 0;
    }

    const Result<entt::meta_any> &value() const override
    {
        return value_;
    }

    AsyncResult<entt::meta_any> read() override
    {
        co_return value_;
    }

    AsyncResult<void> write(entt::meta_any value) override
    {
        value_ = std::move(value);
        co_return Result<void>{};
    }

  private:
    std::string name_;
    Result<entt::meta_any> value_;
};
} // namespace quite::client::test
