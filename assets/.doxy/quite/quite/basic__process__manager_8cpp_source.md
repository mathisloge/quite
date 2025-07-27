

# File basic\_process\_manager.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**basic\_process\_manager.cpp**](basic__process__manager_8cpp.md)

[Go to the documentation of this file](basic__process__manager_8cpp.md)


```C++
#include "quite/manager/basic_process_manager.hpp"
#include "noop_process.hpp"

namespace quite::manager
{
BasicProcessManager::~BasicProcessManager() = default;

ProcessHandle BasicProcessManager::noop_process()
{
    return ProcessHandle{std::make_shared<NoopProcess>()};
}
} // namespace quite::manager
```


