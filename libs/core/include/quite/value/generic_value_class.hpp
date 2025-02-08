#pragma once
#include <string>
#include <entt/container/dense_map.hpp>
#include <entt/meta/meta.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{
struct QUITE_CORE_EXPORT GenericClass
{
    using PropertyMap = entt::dense_map<std::string, entt::meta_any>;
    PropertyMap properties;
};
} // namespace quite
