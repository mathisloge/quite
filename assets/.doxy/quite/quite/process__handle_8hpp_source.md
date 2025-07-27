

# File process\_handle.hpp

[**File List**](files.md) **>** [**include**](dir_4016f4d3acd3fc8991c53702cd4dc6d5.md) **>** [**quite**](dir_b37ea4b54adf6aca6f6e7e088c5d43d6.md) **>** [**manager**](dir_3f8205de661b2b55b021bbc49d05e58b.md) **>** [**process\_handle.hpp**](process__handle_8hpp.md)

[Go to the documentation of this file](process__handle_8hpp.md)


```C++
#pragma once
#include <memory>
#include "quite/quite_manager_export.hpp"

namespace quite::manager
{
class Process;
class QUITE_MANAGER_EXPORT ProcessHandle
{
  public:
    explicit ProcessHandle(std::shared_ptr<Process> process);
    Process &instance();
    Process *operator->();

  private:
    std::shared_ptr<Process> process_;
};
} // namespace quite::manager
```


