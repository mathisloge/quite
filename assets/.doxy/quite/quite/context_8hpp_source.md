

# File context.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**context.hpp**](context_8hpp.md)

[Go to the documentation of this file](context_8hpp.md)


```C++
#pragma once
#include <boost/asio/io_context.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/proto/client/client.hpp>

namespace quite
{
class Context final
{
  public:
    ~Context();
    execpools::asio_thread_pool &asio_context();
    proto::Client &backend_client();

  public:
    static Context &Instance();

  private:
    Context();

  private:
    std::unique_ptr<proto::Client> client_;
};
} // namespace quite
```


