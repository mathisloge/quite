// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <span>
#include <entt/meta/meta.hpp>
#include <quite/result.hpp>
#include <quite/value/value_registry.hpp>

namespace quite::probe
{
class ObjectTracker;
class MethodInvoker
{
  public:
    MethodInvoker();

    Result<entt::meta_any> invoke_method(const entt::meta_any &object,
                                         std::string_view qualified_method_signature,
                                         std::span<entt::meta_any> params) const;
};
} // namespace quite::probe
