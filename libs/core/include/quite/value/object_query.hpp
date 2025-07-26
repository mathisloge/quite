#pragma once
#include <memory>
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include "quite/quite_core_export.hpp"

namespace quite
{
struct QUITE_CORE_EXPORT ObjectQuery
{
    using PropertyMap = std::unordered_map<std::string, entt::meta_any>;
    std::shared_ptr<ObjectQuery> container; // use a shared pointer here, makes the python code gen much easier
    PropertyMap properties;
    std::string type_name;
};

class QUITE_CORE_EXPORT ObjectQueryBuilder
{
    std::shared_ptr<ObjectQuery> query_;

  public:
    ObjectQueryBuilder();

    ObjectQueryBuilder &with_property(std::initializer_list<std::pair<std::string, entt::meta_any>> props);

    ObjectQueryBuilder &with_property(std::string key, std::int64_t value);

    ObjectQueryBuilder &with_property(std::string key, std::uint64_t value);

    ObjectQueryBuilder &with_property(std::string key, double value);

    ObjectQueryBuilder &with_property(std::string key, bool value);

    ObjectQueryBuilder &with_property(std::string key, std::string value);

    ObjectQueryBuilder &with_parent(std::shared_ptr<ObjectQuery> parent);

    ObjectQueryBuilder &with_type(std::string type_name);

    // Implicit conversion to shared_ptr<ObjectQuery>
    operator std::shared_ptr<ObjectQuery>() const;
};

// Factory function
QUITE_CORE_EXPORT ObjectQueryBuilder make_query();

} // namespace quite
template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::ObjectQuery> : fmt::formatter<std::string_view>
{
    auto format(const quite::ObjectQuery &query, format_context &ctx) const -> format_context::iterator;
};
