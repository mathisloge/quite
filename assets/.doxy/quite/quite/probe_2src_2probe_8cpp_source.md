

# File probe.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probe**](dir_ae4f153cafaf07a7427603efac14088a.md) **>** [**src**](dir_060cbf3b90b300eaf029d97551e4bad1.md) **>** [**probe.cpp**](probe_2src_2probe_8cpp.md)

[Go to the documentation of this file](probe_2src_2probe_8cpp.md)


```C++
#include "quite/probe.hpp"
#include <entt/locator/locator.hpp>
#include <probe_context.hpp>
#include <quite/setup_logger.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{
void setup_hooks(GrpcServer server_config)
{
    setup_logger(false);
    entt::locator<probe::ProbeContext>::emplace(server_config.server_address);
}
} // namespace quite
```


