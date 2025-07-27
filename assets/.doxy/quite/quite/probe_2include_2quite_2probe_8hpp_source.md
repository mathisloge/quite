

# File probe.hpp

[**File List**](files.md) **>** [**include**](dir_248610c7c7855733370a23eb8ee334df.md) **>** [**quite**](dir_6ea7810d42f11748e7a5ac93411fd1ce.md) **>** [**probe.hpp**](probe_2include_2quite_2probe_8hpp.md)

[Go to the documentation of this file](probe_2include_2quite_2probe_8hpp.md)


```C++
#pragma once
#include <string>
#include "quite/quite_probe_export.hpp"

namespace quite
{
struct GrpcServer
{
    std::string server_address;
};

PROBE_EXPORT void setup_hooks(GrpcServer server_config = GrpcServer{.server_address = "unix:///tmp/grpc_probe.sock"});
} // namespace quite
```


