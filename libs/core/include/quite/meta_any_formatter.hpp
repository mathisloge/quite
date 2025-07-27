// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include "quite/value/generic_value_class.hpp"

template <>
struct fmt::formatter<entt::meta_any> : fmt::formatter<std::string_view>
{
    auto format(const entt::meta_any &value, format_context &ctx) const -> format_context::iterator
    {
        const auto type = value.type();

        fmt::format_to(ctx.out(), "any(type={}: value=", type.info().name());
        auto value_printer = [&value, &type]() {
            if (type.is_arithmetic())
            {
                return fmt::format("{}", value.allow_cast<double>().cast<double>());
            }
            if (type.is_sequence_container())
            {
                return fmt::format("{}", value.as_sequence_container());
            }
            if (type.is_associative_container())
            {
                return fmt::format("{}", value.as_associative_container());
            }
            if (type.is_class())
            {
                if (type.info() == entt::type_id<std::string>())
                {
                    return value.cast<std::string>();
                }
                if (type.info() == entt::type_id<quite::GenericClass>())
                {
                    return std::string{"todo"};
                }
                return std::string{"no-formatter"};
            }
            return std::string{"unknown"};
        };
        return fmt::format_to(ctx.out(),
                              "any(type_id={}, name={} value={})",
                              value.type().id(),
                              value.type().info().name(),
                              value_printer());
    }
};
