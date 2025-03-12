#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <quite/asio2exec.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/result.hpp>
#include "quite/quite_manager_export.hpp"

namespace quite::manager
{
class Process;
class QUITE_MANAGER_EXPORT ProcessManager
{
  public:
    class ProcessHandle
    {
      public:
        Process &instance();

      private:
        explicit ProcessHandle(std::shared_ptr<Process> app);
        friend class ProcessManager;
        std::shared_ptr<Process> application_;
    };

    struct QtProbe
    {};

    using PID = std::uint64_t;
    using Id = std::string;

  public:
    QUITE_DISABLE_COPY(ProcessManager);
    explicit ProcessManager(asio2exec::asio_context &context);
    ~ProcessManager();
    ProcessManager(ProcessManager &&) noexcept = default;
    ProcessManager &operator=(ProcessManager &&) noexcept = default;

    /**
     * @brief Tries to lookup the application with the given id.
     *
     * @param name the id of the application (which was used to launch or attach a application)
     * @return Result<ProcessHandle> An instance of an application or a not found error otherwise
     */
    Result<ProcessHandle> application(const Id &name);

    /**
     * @brief Launches the application but does not preloads any probe. Can be used to start abitrary installed programs
     *
     * @param id_name a user defined id (name) to retrieve a handle later on
     * @param path_to_application
     * @param args
     * @param environment
     * @return ProcessHandle
     */
    ProcessHandle launch_application(Id id_name,
                                     const std::string &path_to_application,
                                     const std::vector<std::string> &args = {},
                                     const std::unordered_map<std::string, std::string> &environment = {});

    /**
     * @brief Launches the application and preloads the Qt-Probe.
     *
     * @param path_to_application
     * @param args
     * @param environment
     * @return ProcessHandle
     */
    ProcessHandle launch_application(QtProbe,
                                     Id id_name,
                                     const std::string &path_to_application,
                                     const std::vector<std::string> &args = {},
                                     const std::unordered_map<std::string, std::string> &environment = {});

    /**
     * @brief Creates a handle with does nothing.
     *
     * @return ProcessHandle
     */
    ProcessHandle noop_process();

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::manager
