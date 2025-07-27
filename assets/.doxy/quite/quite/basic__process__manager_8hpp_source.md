

# File basic\_process\_manager.hpp

[**File List**](files.md) **>** [**include**](dir_4016f4d3acd3fc8991c53702cd4dc6d5.md) **>** [**quite**](dir_b37ea4b54adf6aca6f6e7e088c5d43d6.md) **>** [**manager**](dir_3f8205de661b2b55b021bbc49d05e58b.md) **>** [**basic\_process\_manager.hpp**](basic__process__manager_8hpp.md)

[Go to the documentation of this file](basic__process__manager_8hpp.md)


```C++
#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
#include <quite/async_result.hpp>
#include "process_handle.hpp"
#include "quite/quite_manager_export.hpp"

namespace quite::manager
{
class Process;
struct QUITE_MANAGER_EXPORT ProcessId
{
    std::string name;
};

class QUITE_MANAGER_EXPORT BasicProcessManager
{
  public:
    using Environment = std::unordered_map<std::string, std::string>;

    virtual ~BasicProcessManager();

    virtual AsyncResult<ProcessHandle> application(ProcessId name) = 0;

    virtual AsyncResult<ProcessHandle> launch_application(ProcessId id,
                                                          std::string path_to_application,
                                                          std::vector<std::string> args,
                                                          Environment environment) = 0;

    virtual AsyncResult<std::filesystem::path> find_executable(std::filesystem::path exe_name,
                                                               Environment environment) = 0;

    static ProcessHandle noop_process();
};
} // namespace quite::manager
```


