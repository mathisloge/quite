

# File value\_converter.hpp

[**File List**](files.md) **>** [**client**](dir_cf009ea199fe2cc3ab30b0598ff08e34.md) **>** [**value\_converter.hpp**](value__converter_8hpp.md)

[Go to the documentation of this file](value__converter_8hpp.md)


```C++
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
```


