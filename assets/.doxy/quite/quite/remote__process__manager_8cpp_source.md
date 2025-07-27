

# File remote\_process\_manager.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**remote\_process\_manager.cpp**](remote__process__manager_8cpp.md)

[Go to the documentation of this file](remote__process__manager_8cpp.md)


```C++
#include "remote_process_manager.hpp"

namespace quite::manager
{
AsyncResult<RemoteProcessManager::Environment> RemoteProcessManager::current_remote_environment()
{}

AsyncResult<ProcessHandle> RemoteProcessManager::application(ProcessId name)
{}

AsyncResult<ProcessHandle> RemoteProcessManager::launch_application(ProcessId id,
                                                                    std::string path_to_application,
                                                                    std::vector<std::string> args,
                                                                    Environment environment)
{}

AsyncResult<std::filesystem::path> RemoteProcessManager::find_executable(std::filesystem::path exe_name,
                                                                         Environment environment)
{}
} // namespace quite::manager
```


