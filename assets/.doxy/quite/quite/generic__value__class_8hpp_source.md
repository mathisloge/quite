

# File generic\_value\_class.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**value**](dir_649c775d6fa8febbabfb9f60e7970e98.md) **>** [**generic\_value\_class.hpp**](generic__value__class_8hpp.md)

[Go to the documentation of this file](generic__value__class_8hpp.md)


```C++
#pragma once
#include <string>
#include <unordered_map>
#include <entt/meta/meta.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{
struct QUITE_CORE_EXPORT GenericClass
{
    using PropertyMap = std::unordered_map<std::string, entt::meta_any>;
    PropertyMap properties;
};
} // namespace quite
```


