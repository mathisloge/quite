

# File qt\_meta\_registry.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**qt\_meta\_registry.hpp**](qt__meta__registry_8hpp.md)

[Go to the documentation of this file](qt__meta__registry_8hpp.md)


```C++
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
```


