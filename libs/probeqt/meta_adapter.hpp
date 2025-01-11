#pragma once
#include <entt/meta/meta.hpp>
#include "result.hpp"

namespace quite::probe
{

class MetaAdapter
{
  public:
    Result<entt::meta_any> search_type_by_qualified_name(std::string_view qualified_type_name);
    Result<entt::meta_any> invoke_method(const entt::meta_any &object,
                                         std::string_view qualified_method_signature,
                                         std::span<entt::meta_any> params) const;
};
} // namespace quite::probe
