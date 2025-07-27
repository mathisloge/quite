// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

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

ProcessManager::ProcessManager(asio_impl::thread_pool::executor_type executor)
    : impl_{std::make_unique<Impl>(std::move(executor))}
{}

ProcessManager::~ProcessManager() = default;

AsyncResult<ProcessHandle> ProcessManager::application(const ProcessId id)
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
                                                              std::string path_to_application,
                                                              std::vector<std::string> args,
                                                              Environment environment)
{
    try
    {
        LOG_DEBUG(process_manager(), "Trying to launch application {}...", path_to_application);
        if (not std::filesystem::exists(path_to_application))
        {
            LOG_DEBUG(process_manager(), "Could not find application as path. Trying to find it in the environment...");
            const auto exe_found_in_env = co_await find_executable(path_to_application, environment);
            if (not exe_found_in_env.has_value())
            {
                LOG_ERROR(process_manager(), "Could not find application as path or in the environment.");
                co_return make_error_result(
                    ErrorCode::not_found,
                    fmt::format("Could not find {} as path or in given environment.", path_to_application));
            }
        }

        bp::process process{impl_->executor_,
                            std::move(path_to_application),
                            std::move(args),
                            bp::process_environment{std::move(environment)}};
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
                                    fmt::format("Could not find {} in environment {}", exe_name, environment));
    }
    co_return std::filesystem::path{exe.string()};
}
} // namespace quite::manager
