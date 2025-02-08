#pragma once
#include <entt/meta/meta.hpp>
#include <quite/value/value_registry.hpp>
#include "quite/proto/types.pb.h"

namespace quite::proto
{
Value create_value(const ValueRegistry &value_registry, const entt::meta_any &type);
}
