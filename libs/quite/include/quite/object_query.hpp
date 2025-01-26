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
    std::shared_ptr<ObjectQuery> container; // use a shared pointer here, makes the python code gen much easier
    std::unordered_map<std::string, Value> properties;
};
} // namespace quite

template <>
struct QUITELIB_EXPORT fmt::formatter<quite::ObjectQuery> : fmt::formatter<std::string_view>
{
    auto format(const quite::ObjectQuery &query, format_context &ctx) const -> format_context::iterator;
};
