#pragma once
#include <string>
#include <unordered_map>
#include <entt/meta/fwd.hpp>
#include <quite/meta/meta_type_id.hpp>

namespace quite::probe
{
struct ClassValue
{
    using MemberName = std::string;

    meta::TypeId type_id;
    std::unordered_map<MemberName, entt::meta_any> properties;
};
} // namespace quite::probe
