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

    /**
     * @brief Tries to lookup the application with the given id.
     *
     * @param name the id of the application (which was used to launch or attach a application)
     * @return Result<ProcessHandle> An instance of an application or a not found error otherwise
     */
    virtual AsyncResult<ProcessHandle> application(const ProcessId &name) = 0;

    /**
     * @brief Launches the application but does not preloads any probe. Can be used to start abitrary installed programs
     *
     * @param id a user defined id (name) to retrieve a handle later on
     * @param path_to_application
     * @param args
     * @param environment
     * @return ProcessHandle
     */
    virtual AsyncResult<ProcessHandle> launch_application(ProcessId id,
                                                          const std::string &path_to_application,
                                                          const std::vector<std::string> &args,
                                                          const Environment &environment) = 0;

    /**
     * @brief Trys to find the given executable in the PATH equivalent enviroment entry.
     *
     * @param exe_name the application name
     * @param environment the environment to search in
     * @return Result<std::filesystem::path> either an error or the absolute path to the executable
     */
    virtual AsyncResult<std::filesystem::path> find_executable(std::filesystem::path exe_name,
                                                               Environment environment) = 0;

    /**
     * @brief Creates a process handle with does nothing, always finished with exit code 0
     *
     * @return ProcessHandle
     */
    static ProcessHandle noop_process();
};
} // namespace quite::manager
