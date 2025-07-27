

# File process\_manager\_client.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**process\_manager\_client.hpp**](process__manager__client_8hpp.md)

[Go to the documentation of this file](process__manager__client_8hpp.md)


```C++
#pragma once
#include <quite/disable_copy_move.hpp>
#include "quite/manager/remote_process_manager.hpp"

namespace quite::manager
{
class Process;
class ProcessManagerClient : public RemoteProcessManager
{
  public:
    QUITE_DISABLE_COPY(ProcessManagerClient);
    QUITE_DEFAULT_MOVE(ProcessManagerClient);
    explicit ProcessManagerClient();
    ~ProcessManagerClient() override;

    Result<ProcessHandle> application(const ProcessId &id) override;
    Result<ProcessHandle> launch_application(ProcessId id,
                                             const std::string &path_to_application,
                                             const std::vector<std::string> &args,
                                             const Environment &environment) override;
    AsyncResult<Environment> current_environment();
    Result<std::filesystem::path> find_executable(std::filesystem::path exe_name, Environment environment) override;
};
} // namespace quite::manager
```


