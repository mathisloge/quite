#include "quite/manager/application_manager.hpp"
#include <boost/process/v2.hpp>
#include <quite/logger.hpp>
#include "application_impl.hpp"

DEFINE_LOGGER(application_manager)

namespace bp = boost::process::v2;

namespace quite::manager
{
struct ApplicationManager::Impl
{
    asio2exec::asio_context &context_;
    std::unordered_map<Id, std::shared_ptr<Application>> applications_;
};

ApplicationManager::ApplicationHandle::ApplicationHandle(std::shared_ptr<Application> app)
    : application_{std::move(app)}
{}

ApplicationManager::~ApplicationManager() = default;

Application &ApplicationManager::ApplicationHandle::instance()
{
    return *application_;
}

ApplicationManager::ApplicationManager(asio2exec::asio_context &context)
    : impl_{std::make_unique<Impl>(context)}
{}

Result<ApplicationManager::ApplicationHandle> ApplicationManager::application(const Id &name)
{
    auto it = impl_->applications_.find(name);
    if (it == impl_->applications_.end())
    {
        return make_error_result<ApplicationHandle>(
            ErrorCode::not_found, fmt::format("Application with id '{}' is not present (anymore)", name));
    }
    return ApplicationHandle{it->second};
}

ApplicationManager::ApplicationHandle ApplicationManager::launch_application(
    Id id_name,
    const std::string &path_to_application,
    const std::vector<std::string> &args,
    const std::unordered_map<std::string, std::string> &environment)
{
    bp::process process{impl_->context_.get_executor(), path_to_application, args, environment};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ApplicationImpl>(std::move(process)));
    return ApplicationHandle{app->second};
}

/**
 * @brief Launches the application and preloads the Qt-Probe.
 *
 * @param path_to_application
 * @param args
 * @param environment
 * @return ApplicationHandle
 */
ApplicationManager::ApplicationHandle ApplicationManager::launch_application(
    QtProbe,
    Id id_name,
    const std::string &path_to_application,
    const std::vector<std::string> &args,
    const std::unordered_map<std::string, std::string> &environment)
{
    bp::process process{impl_->context_.get_executor().get_executor(), path_to_application, args, environment};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ApplicationImpl>(std::move(process)));
    // TODO: add preload of qt probe
    return ApplicationHandle{app->second};
}

/**
 * @brief Attaches the Qt-Probe to the running process.
 *
 * @param process_id
 * @return ApplicationHandle
 */
ApplicationManager::ApplicationHandle ApplicationManager::attach_probe_to_running(QtProbe, Id id_name, PID process_id)
{
    bp::process process{impl_->context_.get_executor().get_executor(), static_cast<bp::pid_type>(process_id)};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ApplicationImpl>(std::move(process)));
    return ApplicationHandle{app->second};
}

/**
 * @brief Attaches to any running process.
 *
 * @param process_id
 * @return ApplicationHandle
 */
ApplicationManager::ApplicationHandle ApplicationManager::attach_to_running(Id id_name, PID process_id)
{
    bp::process process{impl_->context_.get_executor().get_executor(), static_cast<bp::pid_type>(process_id)};
    auto [app, emplaced] =
        impl_->applications_.emplace(std::move(id_name), std::make_shared<ApplicationImpl>(std::move(process)));
    return ApplicationHandle{app->second};
}
} // namespace quite::manager
