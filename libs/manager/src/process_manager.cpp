#include "quite/manager/process_manager.hpp"
#include <filesystem>
#include <boost/process/environment.hpp>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <quite/logger.hpp>
#include "process_impl.hpp"

DEFINE_LOGGER(process_manager)

namespace bp = boost::process::v2;

namespace quite::manager
{
struct ProcessManager::Impl
{
    quite::asio_impl::any_io_executor executor_;
    std::unordered_map<std::string, std::shared_ptr<Process>> applications_;
};

ProcessManager::ProcessManager(const quite::asio_impl::any_io_executor &executor)
    : impl_{std::make_unique<Impl>(executor)}
{}

ProcessManager::~ProcessManager() = default;

AsyncResult<ProcessHandle> ProcessManager::application(const ProcessId &id)
{
    const auto it = impl_->applications_.find(id.name);
    if (it == impl_->applications_.end())
    {
        co_return make_error_result(ErrorCode::not_found,
                                    fmt::format("Process with id '{}' is not present (anymore)", id.name));
    }
    co_return ProcessHandle{it->second};
}

AsyncResult<ProcessHandle> ProcessManager::launch_application(ProcessId id,
                                                              const std::string &path_to_application,
                                                              const std::vector<std::string> &args,
                                                              const Environment &environment)
{
    try
    {
        bp::process process{impl_->executor_, path_to_application, args, bp::process_environment{environment}};
        auto [app, emplaced] = impl_->applications_.insert_or_assign(std::move(id.name),
                                                                     std::make_shared<ProcessImpl>(std::move(process)));
        if (not emplaced)
        {
            LOG_WARNING(process_manager(),
                        "A process with id '{}' was already in place. Replaced with the newly launched process.",
                        app->first);
        }
        co_return ProcessHandle{app->second};
    }
    catch (const boost::system::system_error &e)
    {
        co_return make_error_result(ErrorCode::aborted, e.what());
    }
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

AsyncResult<std::filesystem::path> ProcessManager::find_executable(std::filesystem::path exe_name,
                                                                   Environment environment)
{
    auto exe = bp::environment::find_executable(bp::filesystem::path{std::move(exe_name)}, std::move(environment));
    if (exe.empty())
    {
        co_return make_error_result(ErrorCode::not_found,
                                    fmt::format("Could not find {} in enviroment {}", exe_name, environment));
    }
    co_return std::filesystem::path{exe.string()};
}
} // namespace quite::manager
