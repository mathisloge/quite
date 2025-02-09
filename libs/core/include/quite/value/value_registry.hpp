#pragma once
#include <entt/container/dense_map.hpp>
#include <entt/core/hashed_string.hpp>
#include <entt/locator/locator.hpp>
#include <entt/meta/context.hpp>
#include <entt/meta/meta.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{
class QUITE_CORE_EXPORT ValueRegistry
{
  public:
    using PropertyNameMap = entt::dense_map<entt::id_type, std::string>;

  public:
    entt::id_type named_property(std::string name);
    const PropertyNameMap &property_names() const;
    entt::meta_ctx &context();

  private:
    PropertyNameMap name_db_;
    entt::meta_ctx &context_ = entt::locator<entt::meta_ctx>::value_or();
};
} // namespace quite
