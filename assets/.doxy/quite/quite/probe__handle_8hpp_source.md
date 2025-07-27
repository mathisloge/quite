

# File probe\_handle.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**probe\_handle.hpp**](probe__handle_8hpp.md)

[Go to the documentation of this file](probe__handle_8hpp.md)


```C++
#pragma once
#include <memory>
#include "quite/quite_client_export.hpp"
namespace quite::client
{
class Probe;
class QUITE_CLIENT_EXPORT ProbeHandle
{
  public:
    explicit ProbeHandle(std::shared_ptr<Probe> probe);
    Probe *operator->();

  private:
    std::shared_ptr<Probe> probe_;
};
} // namespace quite::client
```


