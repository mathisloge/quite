#pragma once
#include <cstdint>
#include "quite/meta/meta_type_id.hpp"

namespace quite
{
using ObjectId = std::uint64_t;

struct ObjectReference
{
    ObjectId object_id;
    meta::TypeId type_id;
};
} // namespace quite
