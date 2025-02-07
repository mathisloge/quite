#pragma once
#include <string>
#include <unordered_map>
#include <entt/meta/meta.hpp>
namespace quite::probe
{

struct GenericQtClass
{
    std::unordered_map<std::string, entt::meta_any> properties;
};

void register_converters();
} // namespace quite::probe
