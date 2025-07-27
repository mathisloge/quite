

# File server.hpp

[**File List**](files.md) **>** [**include**](dir_5926395dd2a1a1e5a7c03e8f9928f69e.md) **>** [**quite**](dir_69811da4b5ffa6c48780c3c2aaa473c8.md) **>** [**proto**](dir_e84ba8046b88057ef61cdc53860835dc.md) **>** [**probe**](dir_b0223a4951d67b698dfb269e1d467abc.md) **>** [**server.hpp**](protocol_2include_2quite_2proto_2probe_2server_8hpp.md)

[Go to the documentation of this file](protocol_2include_2quite_2proto_2probe_2server_8hpp.md)


```C++
#pragma once
#include <memory>
#include <string>
#include <entt/locator/locator.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/service_handle.hpp>
#include "quite/quite_protocol_export.hpp"
namespace quite
{
class ValueRegistry;
}
namespace quite::core
{
class IMouseInjector;
}
namespace quite::meta
{
class MetaRegistry;
}

namespace quite::proto
{
class IProbeHandler;

class QUITE_PROTOCOL_EXPORT Server final
{
  public:
    QUITE_DISABLE_COPY(Server);
    Server(std::string server_address,
           ServiceHandle<IProbeHandler> probe_handler,
           ServiceHandle<core::IMouseInjector> mouse_injector,
           ServiceHandle<meta::MetaRegistry> meta_registry,
           ServiceHandle<ValueRegistry> value_registry);
    Server(Server &&server) noexcept;
    Server &operator=(Server &&server) noexcept;
    ~Server();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::proto
```


