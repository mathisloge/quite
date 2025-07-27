

# File remote\_process\_manager.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**remote\_process\_manager.hpp**](remote__process__manager_8hpp.md)

[Go to the documentation of this file](remote__process__manager_8hpp.md)


```C++
#pragma once
#include <quite/async_result.hpp>
#include "quite/manager/basic_process_manager.hpp"

namespace quite::manager
{
class RemoteProcessManager : public BasicProcessManager
{
  public:
    AsyncResult<Environment> current_remote_environment();

    AsyncResult<ProcessHandle> application(ProcessId name) override;
    AsyncResult<ProcessHandle> launch_application(ProcessId id,
                                                  std::string path_to_application,
                                                  std::vector<std::string> args,
                                                  Environment environment) override;
    AsyncResult<std::filesystem::path> find_executable(std::filesystem::path exe_name,
                                                       Environment environment) override;

  private:
};
} // namespace quite::manager
```


