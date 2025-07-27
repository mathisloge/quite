

# File context.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**context.cpp**](context_8cpp.md)

[Go to the documentation of this file](context_8cpp.md)


```C++
#include "context.hpp"
#include <quite/asio_context.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{

Context::Context()
{
    entt::locator<ValueRegistry>::emplace();
    client_ = std::make_unique<proto::Client>(entt::locator<ValueRegistry>::handle());
}

Context::~Context()
{
    get_executor().context().stop();
}

proto::Client &Context::backend_client()
{
    return *client_;
}

execpools::asio_thread_pool &Context::asio_context()
{
    return thread_pool();
}

Context &Context::Instance()
{
    static Context context;
    return context;
}
} // namespace quite
```


