#include "remote_process_manager.hpp"

namespace quite::manager
{
AsyncResult<RemoteProcessManager::Environment> RemoteProcessManager::current_remote_environment()
{}

AsyncResult<ProcessHandle> RemoteProcessManager::application(const ProcessId &name)
{}

AsyncResult<ProcessHandle> RemoteProcessManager::launch_application(ProcessId id,
                                                                    const std::string &path_to_application,
                                                                    const std::vector<std::string> &args,
                                                                    const Environment &environment)
{}

AsyncResult<std::filesystem::path> RemoteProcessManager::find_executable(std::filesystem::path exe_name,
                                                                         Environment environment)
{}
} // namespace quite::manager
