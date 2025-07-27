

# File basic\_probe.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**basic\_probe.hpp**](basic__probe_8hpp.md)

[Go to the documentation of this file](basic__probe_8hpp.md)


```C++
#pragma once
#include <quite/manager/process_handle.hpp>
#include "quite/client/probe.hpp"
namespace quite::client
{
class BasicProbe : public Probe
{
  public:
    explicit BasicProbe(manager::ProcessHandle process);
    manager::Process &process();

    AsyncResult<void> exit() override;

  private:
    manager::ProcessHandle process_;
};
} // namespace quite::client
```


