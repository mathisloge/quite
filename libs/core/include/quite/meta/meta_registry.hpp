#pragma once
#include <quite/async_result.hpp>
#include "meta_types.hpp"
#include "quite_core_export.h"
namespace quite::meta
{
class QUITE_CORE_EXPORT MetaRegistry
{
  public:
    virtual ~MetaRegistry() = default;
    virtual AsyncResult<meta::Type> lookup_type(meta::TypeId type_id) = 0;
};
} // namespace quite::meta
