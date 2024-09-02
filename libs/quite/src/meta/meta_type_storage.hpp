#pragma once
#include <atomic>
#include <unordered_map>
#include <entt/core/hashed_string.hpp>
#include "quite/meta/meta_types.hpp"

namespace quite::meta
{
class MetaTypeStorage final
{
  public:
    std::atomic_uint32_t id_counter_;
    std::unordered_map<std::uint32_t, Type> registered_types_;
    std::unordered_map<entt::hashed_string::hash_type, std::uint32_t> type_name_lookup_;
};
} // namespace quite::meta