#include "process_application.hpp"
#include <boost/asio/steady_timer.hpp>
#include <exec/when_any.hpp>
#include <quite/logger.hpp>
#include "quite/quite.hpp"

DEFINE_LOGGER(process_application_logger)

namespace quite
{
ProcessApplication::ProcessApplication(Context &context,
                                       const std::string &path_to_application,
                                       const std::vector<std::string> &args,
                                       const std::unordered_map<std::string, std::string> &enviroment)
    : GrpcApplication(context)
    , process_{quite::asio_context().get_executor(),
               path_to_application,
               args,
               enviroment,
               boost::process::process_stdio{{}, {}, {}}}
{
    do_read();
}

ProcessApplication::~ProcessApplication()
{
    LOG_DEBUG(process_application_logger(), "finished");
}

AsyncResult<void> ProcessApplication::exit()
{
    if (process_.is_open())
    {
        LOG_DEBUG(process_application_logger(), "Process still running. Trying to gracefully stop it.");
        boost::asio::steady_timer timer{quite::asio_context().get_executor(), std::chrono::seconds(3)};
        boost::system::error_code ec;
        process_.request_exit(ec);
        co_await exec::when_any(
            process_.async_wait(asio2exec::use_sender) | stdexec::then([](auto &&error_code, auto &&) {
                if (error_code)
                {
                    LOG_ERROR(
                        process_application_logger(), "Could not wait for process. Error: {}", error_code.message());
                    throw std::system_error{std::forward<decltype(error_code)>(error_code)};
                }
                LOG_DEBUG(process_application_logger(), "Process stopped successfully");
            }),
            timer.async_wait(asio2exec::use_sender) | stdexec::then([this](std::error_code ec) {
                if (ec)
                {
                    LOG_ERROR(process_application_logger(), "Could not wait for timer. Error: {}", ec.message());
                    throw std::system_error{std::move(ec)};
                }
                LOG_DEBUG(process_application_logger(),
                          "Could not stop process gracefully. Going to terminate the process.");
                process_.terminate();
            }));
    }
    co_return {};
}

void ProcessApplication::do_read()
{
    // stdout_pipe_.async_read_some(boost::asio::buffer(buffer_), [this](std::error_code ec, std::size_t length) {
    //     if (!ec)
    //     {
    //         LOG_DEBUG(process_application_logger(), "stdout: {}", std::string_view{buffer_.begin(), length});
    //         do_read();
    //     }
    // });
    //
    // stderr_pipe_.async_read_some(boost::asio::buffer(buffer_), [this](std::error_code ec, std::size_t length) {
    //     if (!ec)
    //     {
    //         LOG_DEBUG(process_application_logger(), "stderr: {}", std::string_view{buffer_.begin(), length});
    //         do_read();
    //     }
    // });
}
} // namespace quite
