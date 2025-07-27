

# File noop\_process.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**noop\_process.cpp**](noop__process_8cpp.md)

[Go to the documentation of this file](noop__process_8cpp.md)


```C++
#include "noop_process.hpp"

namespace quite::manager
{
bool NoopProcess::is_running()
{
    return true;
}

int NoopProcess::exit_code()
{
    return EXIT_SUCCESS;
}

AsyncResult<int> NoopProcess::async_wait_exit()
{
    co_return exit_code();
}

Result<void> NoopProcess::request_exit()
{
    return {};
}

Result<void> NoopProcess::terminate()
{
    return {};
}

} // namespace quite::manager
```


