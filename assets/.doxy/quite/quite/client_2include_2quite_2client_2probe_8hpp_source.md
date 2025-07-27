

# File probe.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**probe.hpp**](client_2include_2quite_2client_2probe_8hpp.md)

[Go to the documentation of this file](client_2include_2quite_2client_2probe_8hpp.md)


```C++
#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/error.hpp>
#include <quite/meta/meta_registry.hpp>
#include <quite/value/object_query.hpp>
#include "quite/quite_client_export.hpp"
#include "remote_object.hpp"
namespace quite::client
{
class QUITE_CLIENT_EXPORT Probe
{
  public:
    QUITE_DISABLE_COPY_MOVE(Probe);
    Probe() = default;
    virtual ~Probe() = default;
    virtual AsyncResult<RemoteObjectPtr> find_object(ObjectQuery query) = 0;
    virtual AsyncResult<std::vector<RemoteObjectPtr>> get_views() = 0;
    virtual AsyncResult<void> wait_for_started(std::chrono::seconds timeout) = 0;
    virtual AsyncResult<void> exit() = 0;
    virtual meta::MetaRegistry &meta_registry() = 0;
};
} // namespace quite::client
```


