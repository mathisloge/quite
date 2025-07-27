

# File quite.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**quite.cpp**](quite_8cpp.md)

[Go to the documentation of this file](quite_8cpp.md)


```C++
#include "quite/client/quite.hpp"
#include "context.hpp"

namespace quite::client
{
execpools::asio_thread_pool &asio_context()
{
    return Context::Instance().asio_context();
}
} // namespace quite::client
```


