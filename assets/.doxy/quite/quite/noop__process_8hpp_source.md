

# File noop\_process.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**noop\_process.hpp**](noop__process_8hpp.md)

[Go to the documentation of this file](noop__process_8hpp.md)


```C++
#pragma once
#include "quite/manager/process.hpp"

namespace quite::manager
{
class NoopProcess final : public Process
{
  public:
    bool is_running() override;
    int exit_code() override;
    AsyncResult<int> async_wait_exit() override;
    Result<void> request_exit() override;
    Result<void> terminate() override;
};
} // namespace quite::manager
```


