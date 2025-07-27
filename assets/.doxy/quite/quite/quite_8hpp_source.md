

# File quite.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**quite.hpp**](quite_8hpp.md)

[Go to the documentation of this file](quite_8hpp.md)


```C++
#pragma once
#include <boost/asio/any_io_executor.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include "quite/quite_client_export.hpp"

namespace quite::client
{
QUITE_CLIENT_EXPORT execpools::asio_thread_pool &asio_context();
} // namespace quite::client
```


