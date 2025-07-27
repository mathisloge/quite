

# File asio\_context.cpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**src**](dir_232ab8dc75117fda122ab855789b1b2c.md) **>** [**asio\_context.cpp**](asio__context_8cpp.md)

[Go to the documentation of this file](asio__context_8cpp.md)


```C++
#include <entt/locator/locator.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/asio_context.hpp>

namespace quite
{
execpools::asio_thread_pool &thread_pool()
{
    return entt::locator<execpools::asio_thread_pool>::value_or(2);
}

auto get_executor() -> decltype(thread_pool().get_executor())
{
    return thread_pool().get_executor();
}
} // namespace quite
```


