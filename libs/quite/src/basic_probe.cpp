#include "basic_probe.hpp"
#include <boost/asio/steady_timer.hpp>
#include <exec/when_any.hpp>
#include <quite/logger.hpp>
#include <quite/manager/process.hpp>
#include "quite/quite.hpp"

DEFINE_LOGGER(basic_probe)
namespace quite::client
{
BasicProbe::BasicProbe(manager::ProcessHandle process)
    : process_{std::move(process)}
{}

AsyncResult<void> BasicProbe::exit()
{
    if (not process_.instance().is_running())
    {
        co_return {};
    }
    LOG_DEBUG(basic_probe(), "Process still running. Trying to gracefully stop it.");
    boost::asio::steady_timer timer{quite::asio_context().get_executor(), std::chrono::seconds(3)};
    boost::system::error_code ec;
    std::ignore = process_.instance().request_exit();

    auto exit_result = co_await exec::when_any(
        process_.instance().async_wait_exit(),
        timer.async_wait(asio2exec::use_sender) | stdexec::then([this](std::error_code ec) -> Result<int> {
            if (ec)
            {
                LOG_ERROR(basic_probe(), "Could not wait for timer. Error: {}", ec.message());
                return make_error_result<int>(ErrorCode::cancelled, ec.message());
            }
            LOG_WARNING(basic_probe(), "Could not stop process gracefully. Going to terminate the process.");
            return process_.instance().terminate().transform([]() -> int { return EXIT_FAILURE; });
        }));

    if (exit_result.has_value())
    {
        LOG_INFO(basic_probe(), "Process stopped successfully with exit code {}", exit_result.value());
    }
    else
    {
        LOG_ERROR(basic_probe(), "Could not wait for process. Error: {}", fmt::format("{}", exit_result.error()));
    }
    co_return exit_result.transform([](int /* exit_code */) {});
}

manager::Process &BasicProbe::process()
{
    return process_.instance();
}
} // namespace quite::client
