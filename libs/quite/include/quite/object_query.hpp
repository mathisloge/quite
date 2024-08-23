#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <fmt/ranges.h>
#include "property.hpp"
#include "quitelib_export.h"

namespace quite
{
struct ObjectQuery
{
    std::unique_ptr<ObjectQuery> container;
    std::unordered_map<std::string, Value> properties;
};
} // namespace quite

template <>
struct QUITELIB_EXPORT fmt::formatter<quite::ObjectQuery> : fmt::formatter<std::string_view>
{
    auto format(const quite::ObjectQuery &query, format_context &ctx) const -> format_context::iterator;
};
