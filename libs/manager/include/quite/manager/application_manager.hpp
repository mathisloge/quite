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
class Application;
class QUITE_MANAGER_EXPORT ApplicationManager
{
  public:
    class ApplicationHandle
    {
      public:
        Application &instance();

      private:
        explicit ApplicationHandle(std::shared_ptr<Application> app);
        friend class ApplicationManager;
        std::shared_ptr<Application> application_;
    };

    struct QtProbe
    {};

    using PID = std::uint64_t;
    using Id = std::string;

  public:
    QUITE_DISABLE_COPY(ApplicationManager);
    explicit ApplicationManager(asio2exec::asio_context &context);
    ~ApplicationManager();
    ApplicationManager(ApplicationManager &&) noexcept = default;
    ApplicationManager &operator=(ApplicationManager &&) noexcept = default;

    /**
     * @brief Tries to lookup the application with the given id.
     *
     * @param name the id of the application (which was used to launch or attach a application)
     * @return Result<ApplicationHandle> An instance of an application or a not found error otherwise
     */
    Result<ApplicationHandle> application(const Id &name);

    /**
     * @brief Launches the application but does not preloads any probe. Can be used to start abitrary installed programs
     *
     * @param id_name a user defined id (name) to retrieve a handle later on
     * @param path_to_application
     * @param args
     * @param environment
     * @return ApplicationHandle
     */
    ApplicationHandle launch_application(Id id_name,
                                         const std::string &path_to_application,
                                         const std::vector<std::string> &args = {},
                                         const std::unordered_map<std::string, std::string> &environment = {});

    /**
     * @brief Launches the application and preloads the Qt-Probe.
     *
     * @param path_to_application
     * @param args
     * @param environment
     * @return ApplicationHandle
     */
    ApplicationHandle launch_application(QtProbe,
                                         Id id_name,
                                         const std::string &path_to_application,
                                         const std::vector<std::string> &args = {},
                                         const std::unordered_map<std::string, std::string> &environment = {});

    /**
     * @brief Attaches the Qt-Probe to the running process.
     *
     * @param process_id
     * @return ApplicationHandle
     */
    ApplicationHandle attach_probe_to_running(QtProbe, Id id_name, PID process_id);

    /**
     * @brief Attaches to any running process.
     *
     * @param process_id
     * @return ApplicationHandle
     */
    ApplicationHandle attach_to_running(Id id_name, PID process_id);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::manager
