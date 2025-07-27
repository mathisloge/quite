

# File meta\_adapter.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**meta\_adapter.cpp**](meta__adapter_8cpp.md)

[Go to the documentation of this file](meta__adapter_8cpp.md)


```C++
#include "meta_adapter.hpp"

namespace quite::probe
{

AsyncResult<meta::Type> MetaAdapter::find_type_by_id(meta::TypeId type_id)
{
    return type_registry_.lookup_type(type_id);
}
} // namespace quite::probe
```


