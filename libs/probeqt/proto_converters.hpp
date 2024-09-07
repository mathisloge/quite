#pragma once
#include <entt/meta/meta.hpp>
#include <quite/proto/types.pb.h>

namespace quite::probe
{
entt::meta_any meta_from_value(const proto::Value &value);
} // namespace quite::probe
