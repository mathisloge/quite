

# File meta\_adapter.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**meta\_adapter.hpp**](meta__adapter_8hpp.md)

[Go to the documentation of this file](meta__adapter_8hpp.md)


```C++
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
```


