

# File probe\_handle.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**probe\_handle.cpp**](probe__handle_8cpp.md)

[Go to the documentation of this file](probe__handle_8cpp.md)


```C++
#include "quite/client/probe_handle.hpp"

namespace quite::client
{
ProbeHandle::ProbeHandle(std::shared_ptr<Probe> probe)
    : probe_{std::move(probe)}
{}

Probe *ProbeHandle::operator->()
{
    return probe_.get();
}
} // namespace quite::client
```


