// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/meta/meta_registry.hpp>

namespace quite::proto::test
{
class FakeMetaRegistry final : public meta::MetaRegistry
{
  public:
    explicit FakeMetaRegistry(meta::Type type)
        : type_(std::move(type))
    {}

    AsyncResult<meta::Type> lookup_type(meta::TypeId /*type_id*/) override
    {
        // meta::Type holds unique_ptr alternatives (EnumType/ObjectType), so it's move-only.
        co_return std::move(type_);
    }

  private:
    meta::Type type_;
};
} // namespace quite::proto::test
