#pragma once
#include "quite/proto/client/value_converter.hpp"
namespace quite::proto
{
class ProbeValueConverter final : public IValueConverter
{
    entt::meta_any from(ObjectReference ref) const override
    {
        return entt::forward_as_meta(std::move(ref));
    }
};
} // namespace quite::proto
