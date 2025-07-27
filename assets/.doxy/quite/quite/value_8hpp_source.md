

# File value.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**value.hpp**](value_8hpp.md)

[Go to the documentation of this file](value_8hpp.md)


```C++
#pragma once
#include <entt/meta/meta.hpp>
#include <quite/value/value_registry.hpp>
#include "quite/proto/client/value_converter.hpp"
#include "quite/proto/types.pb.h"

namespace quite::proto
{
Value create_value(const ValueRegistry &value_registry, const entt::meta_any &type);
entt::meta_any convert_value(const ValueRegistry &value_registry, const IValueConverter &converter, const Value &value);
} // namespace quite::proto
```


