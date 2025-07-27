

# File async\_result.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**async\_result.hpp**](async__result_8hpp.md)

[Go to the documentation of this file](async__result_8hpp.md)


```C++
#pragma once
#include <exec/task.hpp>
#include "result.hpp"

namespace quite
{
template <typename T>
using AsyncResult = exec::task<Result<T>>;
}
```


