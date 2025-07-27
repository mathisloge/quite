

# File process\_manager.hpp

[**File List**](files.md) **>** [**include**](dir_4016f4d3acd3fc8991c53702cd4dc6d5.md) **>** [**quite**](dir_b37ea4b54adf6aca6f6e7e088c5d43d6.md) **>** [**manager**](dir_3f8205de661b2b55b021bbc49d05e58b.md) **>** [**process\_manager.hpp**](process__manager_8hpp.md)

[Go to the documentation of this file](process__manager_8hpp.md)


```C++
#pragma once
#include <filesystem>
#include <vector>
#include <quite/asio_config.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/result.hpp>
#include "basic_process_manager.hpp"
#include "process_handle.hpp"
#include "quite/quite_manager_export.hpp"

namespace quite::manager
{
class QUITE_MANAGER_EXPORT ProcessManager : public BasicProcessManager
{
  public:
    QUITE_DISABLE_COPY(ProcessManager);
    QUITE_DEFAULT_MOVE(ProcessManager);
    explicit ProcessManager(asio_impl::thread_pool::executor_type executor);
    ~ProcessManager() override;

    AsyncResult<ProcessHandle> application(ProcessId id) override;

    AsyncResult<ProcessHandle> launch_application(ProcessId id,
                                                  std::string path_to_application,
                                                  std::vector<std::string> args = {},
                                                  Environment environment = current_environment()) override;

    static Environment current_environment();

    AsyncResult<std::filesystem::path> find_executable(std::filesystem::path exe_name,
                                                       Environment environment = current_environment()) override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::manager
```


