

# File probe\_manager.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**probe\_manager.hpp**](client_2include_2quite_2client_2probe__manager_8hpp.md)

[Go to the documentation of this file](client_2include_2quite_2client_2probe__manager_8hpp.md)


```C++
#pragma once
#include <memory>
#include <quite/disable_copy_move.hpp>
#include <quite/manager/process_manager.hpp>
#include "probe_handle.hpp"
#include "quite/quite_client_export.hpp"

namespace quite::client
{
class QUITE_CLIENT_EXPORT ProbeManager
{
  public:
    QUITE_DISABLE_COPY(ProbeManager);
    ProbeManager();
    ~ProbeManager();
    ProbeManager(ProbeManager &&) noexcept = default;
    ProbeManager &operator=(ProbeManager &&) noexcept = default;

    ProbeHandle connect(manager::ProcessHandle handle, const std::string &connection_url);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::client
```


