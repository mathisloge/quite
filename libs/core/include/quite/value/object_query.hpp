#pragma once
#include <memory>
#include <entt/container/dense_map.hpp>
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include "quite/quite_core_export.hpp"

namespace quite
{
struct QUITE_CORE_EXPORT ObjectQuery
{
    using PropertyMap = entt::dense_map<std::string, entt::meta_any>;
    std::shared_ptr<ObjectQuery> container; // use a shared pointer here, makes the python code gen much easier
    PropertyMap properties;
};
} // namespace quite
template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::ObjectQuery> : fmt::formatter<std::string_view>
{
    auto format(const quite::ObjectQuery &query, format_context &ctx) const -> format_context::iterator;
};
