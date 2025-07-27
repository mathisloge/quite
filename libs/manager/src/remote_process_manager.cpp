// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

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
