

# File process.hpp

[**File List**](files.md) **>** [**include**](dir_4016f4d3acd3fc8991c53702cd4dc6d5.md) **>** [**quite**](dir_b37ea4b54adf6aca6f6e7e088c5d43d6.md) **>** [**manager**](dir_3f8205de661b2b55b021bbc49d05e58b.md) **>** [**process.hpp**](process_8hpp.md)

[Go to the documentation of this file](process_8hpp.md)


```C++
#pragma once
#include <quite/async_result.hpp>
#include "quite/quite_manager_export.hpp"
namespace quite::manager
{
class QUITE_MANAGER_EXPORT Process
{
  public:
    virtual ~Process() = default;
    virtual bool is_running() = 0;
    virtual int exit_code() = 0;
    virtual AsyncResult<int> async_wait_exit() = 0;
    virtual Result<void> request_exit() = 0;
    virtual Result<void> terminate() = 0;
};
} // namespace quite::manager
```


