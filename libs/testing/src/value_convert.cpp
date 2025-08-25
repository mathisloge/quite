// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "value_convert.hpp"
#include <fmt/base.h>
#include <quite/client/remote_object.hpp>
#include <quite/logger.hpp>
#include <quite/meta_any_formatter.hpp>
#include <quite/value/object_id.hpp>
#include "quite/test/remote_object.hpp"

DEFINE_LOGGER(test_value_convert);
template <class... Ts>
struct overloads : Ts...
{
    using Ts::operator()...;
};

namespace quite::test
{
Property::Value convert_any(const entt::meta_any &value)
{
    LOG_INFO(test_value_convert(), "CONVERT ANY:{}", fmt::format("{}", value));
    const auto type = value.type();

    if (type.is_arithmetic())
    {
        if (type.info() == entt::type_id<bool>())
        {
            return value.cast<bool>();
        }
        if (type.is_integral())
        {
            if (type.is_signed())
            {
                return value.allow_cast<std::int64_t>().cast<int64_t>();
            }
            return value.allow_cast<std::uint64_t>().cast<uint64_t>();
        }
        return value.allow_cast<double>().cast<double>();
    }

    if (type.is_pointer_like())
    {
        if (type.info() == entt::type_id<client::RemoteObjectPtr>())
        {
            return RemoteObject{value.cast<client::RemoteObjectPtr>()};
        }
    }

    if (type.is_class())
    {
        if (type.info() == entt::type_id<std::string>())
        {
            return value.cast<std::string>();
        }
    }

    return {};
}

entt::meta_any convert_any(Property::Value value)
{
    return std::visit(overloads{[](bool value) { return entt::meta_any{value}; },
                                [](std::uint64_t value) { return entt::meta_any{value}; },
                                [](std::int64_t value) { return entt::meta_any{value}; },
                                [](double value) { return entt::meta_any{value}; },
                                [](std::string value) { return entt::meta_any{std::move(value)}; },
                                [](RemoteObject value) {
                                    return entt::meta_any{
                                        ObjectReference{.object_id = value.underlying_object()->id()}};
                                }},
                      std::move(value));
}
} // namespace quite::test
