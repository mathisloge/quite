

# File probe\_value\_converter.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**probe\_value\_converter.hpp**](probe__value__converter_8hpp.md)

[Go to the documentation of this file](probe__value__converter_8hpp.md)


```C++
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
```


