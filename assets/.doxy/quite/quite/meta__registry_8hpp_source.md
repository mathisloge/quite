

# File meta\_registry.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**meta**](dir_18a9029093157c789cf17586512ae04d.md) **>** [**meta\_registry.hpp**](meta__registry_8hpp.md)

[Go to the documentation of this file](meta__registry_8hpp.md)


```C++
#pragma once
#include <quite/async_result.hpp>
#include "meta_types.hpp"
#include "quite/quite_core_export.hpp"
namespace quite::meta
{
class QUITE_CORE_EXPORT MetaRegistry
{
  public:
    virtual ~MetaRegistry() = default;
    virtual AsyncResult<meta::Type> lookup_type(meta::TypeId type_id) = 0;
};
} // namespace quite::meta
```


