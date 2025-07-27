

# File asio\_context.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**asio\_context.hpp**](asio__context_8hpp.md)

[Go to the documentation of this file](asio__context_8hpp.md)


```C++
#pragma once
#include <execpools/asio/asio_thread_pool.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{

QUITE_CORE_EXPORT execpools::asio_thread_pool &thread_pool();

QUITE_CORE_EXPORT auto get_executor() -> decltype(thread_pool().get_executor());

} // namespace quite
```


