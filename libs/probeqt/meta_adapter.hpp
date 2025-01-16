#pragma once
#include <quite/meta/meta_types.hpp>
#include <quite/result.hpp>
#include "qt_meta_registry.hpp"

namespace quite::probe
{

class MetaAdapter
{
  public:
    AsyncResult<meta::Type> find_type_by_id(meta::TypeId type_id);

  private:
    QtMetaRegistry type_registry_;
};
} // namespace quite::probe
