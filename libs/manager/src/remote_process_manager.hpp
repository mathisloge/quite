#pragma once
#include <quite/async_result.hpp>
#include "quite/manager/basic_process_manager.hpp"

namespace quite::manager
{
class RemoteProcessManager : public BasicProcessManager
{
  public:
    /**
     * @brief Tries to fetch the remote environment from the connected process manager.
     *
     * @return AsyncResult<Environment>
     */
    AsyncResult<Environment> current_remote_environment();

    AsyncResult<ProcessHandle> application(const ProcessId &name) override;
    AsyncResult<ProcessHandle> launch_application(ProcessId id,
                                                  const std::string &path_to_application,
                                                  const std::vector<std::string> &args,
                                                  const Environment &environment) override;
    AsyncResult<std::filesystem::path> find_executable(std::filesystem::path exe_name,
                                                       Environment environment) override;

  private:
};
} // namespace quite::manager
