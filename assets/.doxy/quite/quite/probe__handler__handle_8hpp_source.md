

# File probe\_handler\_handle.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**probe\_handler\_handle.hpp**](probe__handler__handle_8hpp.md)

[Go to the documentation of this file](probe__handler__handle_8hpp.md)


```C++
#pragma once
#include <quite/service_handle.hpp>
#include "quite/proto/probe/probe_handler.hpp"
namespace quite::proto
{
class IProbeHandler;
using ProbeHandlerHandle = ServiceHandle<IProbeHandler>;
} // namespace quite::proto
```


