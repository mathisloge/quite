#pragma once
#include <quite/value/object_id.hpp>

class QObject;
namespace quite::probe
{
constexpr ObjectId to_object_id(const QObject *obj)
{
    return reinterpret_cast<std::uintptr_t>(obj);
}

constexpr QObject *from_object_id(ObjectId obj_id)
{
    return reinterpret_cast<QObject *>(obj_id);
}
} // namespace quite::probe
