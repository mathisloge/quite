

# File object\_id.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**value**](dir_649c775d6fa8febbabfb9f60e7970e98.md) **>** [**object\_id.hpp**](object__id_8hpp.md)

[Go to the documentation of this file](object__id_8hpp.md)


```C++
#pragma once
#include <cstdint>
#include "quite/meta/meta_type_id.hpp"

namespace quite
{
using ObjectId = std::uint64_t;

struct ObjectReference
{
    ObjectId object_id;
    meta::TypeId type_id;
};
} // namespace quite
```


