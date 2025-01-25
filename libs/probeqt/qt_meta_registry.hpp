#pragma once
#include <quite/meta/meta_registry.hpp>

namespace quite::probe
{
class QtMetaRegistry : public meta::MetaRegistry
{
  public:
    AsyncResult<meta::Type> lookup_type(meta::TypeId type_id) override;
};
} // namespace quite::probe
