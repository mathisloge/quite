#pragma once
#include <entt/meta/meta.hpp>
#include <quite/value/object_id.hpp>
#include "quite/quite_protocol_export.hpp"
namespace quite::proto
{
class QUITE_PROTOCOL_EXPORT IValueConverter
{
  public:
    virtual ~IValueConverter() = default;
    virtual entt::meta_any from(ObjectReference ref) const = 0;
};
} // namespace quite::proto
