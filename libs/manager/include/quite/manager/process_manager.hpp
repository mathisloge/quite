#pragma once
#include <filesystem>
#include <vector>
#include <quite/asio2exec.hpp>
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
    explicit ProcessManager(asio2exec::asio_context &context);
    ~ProcessManager() override;

    /**
     * @brief Tries to lookup the application with the given id.
     *
     * @param id the id of the application (which was used to launch or attach a application)
     * @return Result<ProcessHandle> An instance of an application or a not found error otherwise
     */
    Result<ProcessHandle> application(const ProcessId &id) override;

    /**
     * @brief Launches the application but does not preloads any probe. Can be used to start abitrary installed programs
     *
     * @param id_name a user defined id (name) to retrieve a handle later on
     * @param path_to_application
     * @param args
     * @param environment
     * @return ProcessHandle
     */
    Result<ProcessHandle> launch_application(ProcessId id,
                                             const std::string &path_to_application,
                                             const std::vector<std::string> &args = {},
                                             const Environment &environment = current_environment()) override;

    /**
     * @brief Returns the current environment of the running process where the ProcessManager lives
     *
     * @return Environment
     */
    static Environment current_environment();

    /**
     * @brief Trys to find the given executable in the PATH equivalent enviroment entry.
     *
     * @param exe_name the application name
     * @param environment the environment to search in
     * @return Result<std::filesystem::path> either an error or the absolute path to the executable
     */
    Result<std::filesystem::path> find_executable(std::filesystem::path exe_name,
                                                  Environment environment = current_environment()) override;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::manager
