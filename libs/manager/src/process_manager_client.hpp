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
