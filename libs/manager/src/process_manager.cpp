#include "quite/manager/process_manager.hpp"
#include <boost/process/v2.hpp>
#include <quite/logger.hpp>
#include "process_impl.hpp"

DEFINE_LOGGER(process_manager)

namespace bp = boost::process::v2;

namespace quite::manager
{
struct ProcessManager::Impl
{
    asio2exec::asio_context &context_;
    std::unordered_map<Id, std::shared_ptr<Process>> applications_;
};

ProcessManager::ProcessHandle::ProcessHandle(std::shared_ptr<Process> app)
    : application_{std::move(app)}
{}

ProcessManager::~ProcessManager() = default;

Process &ProcessManager::ProcessHandle::instance()
{
    return *application_;
}

ProcessManager::ProcessManager(asio2exec::asio_context &context)
    : impl_{std::make_unique<Impl>(context)}
{}

Result<ProcessManager::ProcessHandle> ProcessManager::application(const Id &name)
{
    auto it = impl_->applications_.find(name);
    if (it == impl_->applications_.end())
    {
        return make_error_result<ProcessHandle>(ErrorCode::not_found,
                                                fmt::format("Process with id '{}' is not present (anymore)", name));
    }
    return ProcessHandle{it->second};
}

ProcessManager::ProcessHandle ProcessManager::launch_application(
    Id id_name,
    const std::string &path_to_application,
    const std::vector<std::string> &args,
    const std::unordered_map<std::string, std::string> &environment)
{
    bp::process process{impl_->context_.get_executor(), path_to_application, args, environment};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ProcessImpl>(std::move(process)));
    return ProcessHandle{app->second};
}

/**
 * @brief Launches the application and preloads the Qt-Probe.
 *
 * @param path_to_application
 * @param args
 * @param environment
 * @return ProcessHandle
 */
ProcessManager::ProcessHandle ProcessManager::launch_application(
    QtProbe,
    Id id_name,
    const std::string &path_to_application,
    const std::vector<std::string> &args,
    const std::unordered_map<std::string, std::string> &environment)
{
    bp::process process{impl_->context_.get_executor().get_executor(), path_to_application, args, environment};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ProcessImpl>(std::move(process)));
    // TODO: add preload of qt probe
    return ProcessHandle{app->second};
}

/**
 * @brief Attaches the Qt-Probe to the running process.
 *
 * @param process_id
 * @return ProcessHandle
 */
ProcessManager::ProcessHandle ProcessManager::attach_probe_to_running(QtProbe, Id id_name, PID process_id)
{
    bp::process process{impl_->context_.get_executor().get_executor(), static_cast<bp::pid_type>(process_id)};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ProcessImpl>(std::move(process)));
    return ProcessHandle{app->second};
}

/**
 * @brief Attaches to any running process.
 *
 * @param process_id
 * @return ProcessHandle
 */
ProcessManager::ProcessHandle ProcessManager::attach_to_running(Id id_name, PID process_id)
{
    bp::process process{impl_->context_.get_executor().get_executor(), static_cast<bp::pid_type>(process_id)};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ProcessImpl>(std::move(process)));
    return ProcessHandle{app->second};
}
} // namespace quite::manager
