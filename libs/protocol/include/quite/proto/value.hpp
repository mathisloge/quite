#pragma once
#include <entt/meta/meta.hpp>
#include "quite/proto/types.pb.h"

namespace quite::proto
{
Value create_value(const entt::dense_map<entt::hashed_string::hash_type, std::string> &property_name_db,
                   const entt::meta_any &type);
}
