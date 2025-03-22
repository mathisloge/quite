#include "quite/manager/process_manager.hpp"
#include <filesystem>
#include <boost/process/v2.hpp>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <quite/logger.hpp>
#include "noop_process.hpp"
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

Process *ProcessManager::ProcessHandle::operator->()
{
    return application_.get();
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

Result<ProcessManager::ProcessHandle> ProcessManager::launch_application(Id id_name,
                                                                         const std::string &path_to_application,
                                                                         const std::vector<std::string> &args,
                                                                         const Environment &environment)
{
    try
    {
        bp::process process{
            impl_->context_.get_executor(), path_to_application, args, bp::process_environment{environment}};
        auto [app, emplaced] = impl_->applications_.insert_or_assign(std::move(id_name),
                                                                     std::make_shared<ProcessImpl>(std::move(process)));
        if (not emplaced)
        {
            LOG_WARNING(process_manager(),
                        "A process with id '{}' was already in place. Replaced with the newly launched process.",
                        app->first);
        }
        return ProcessHandle{app->second};
    }
    catch (const boost::system::system_error &e)
    {
        return make_error_result<ProcessHandle>(ErrorCode::aborted, e.what());
    }
}

Result<ProcessManager::ProcessHandle> ProcessManager::launch_application(QtProbe /*qt-tag*/,
                                                                         Id id_name,
                                                                         const std::string &path_to_application,
                                                                         const std::vector<std::string> &args,
                                                                         const Environment &environment)
{
    return launch_application(id_name, path_to_application, args, environment);
}

ProcessManager::ProcessHandle ProcessManager::noop_process()
{
    return ProcessHandle{std::make_shared<NoopProcess>()};
}

ProcessManager::Environment ProcessManager::current_environment()
{
    ProcessManager::Environment env;
    auto &&c = bp::environment::current();
    for (auto &&kv : c)
    {
        env.emplace(kv.key().string(), kv.value().string());
    }
    return env;
}

Result<std::filesystem::path> ProcessManager::find_executable(std::filesystem::path exe_name, Environment environment)
{
    auto exe = bp::environment::find_executable(bp::filesystem::path{std::move(exe_name)}, std::move(environment));
    if (exe.empty())
    {
        return make_error_result<std::filesystem::path>(
            ErrorCode::not_found, fmt::format("Could not find {} in enviroment {}", exe_name, environment));
    }
    return std::filesystem::path{exe.string()};
}
} // namespace quite::manager
