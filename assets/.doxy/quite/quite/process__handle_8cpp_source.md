

# File process\_handle.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**process\_handle.cpp**](process__handle_8cpp.md)

[Go to the documentation of this file](process__handle_8cpp.md)


```C++
#include "quite/manager/process_handle.hpp"
namespace quite::manager
{
ProcessHandle::ProcessHandle(std::shared_ptr<Process> process)
    : process_{std::move(process)}
{}

Process &ProcessHandle::instance()
{
    return *process_;
}

Process *ProcessHandle::operator->()
{
    return process_.get();
}
} // namespace quite::manager
```


