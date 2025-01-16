#include "process_application.hpp"
#include <quite/logger.hpp>

DEFINE_LOGGER(process_application_logger)

namespace quite
{
ProcessApplication::ProcessApplication(Context &context, const std::string &path_to_application)
    : GrpcApplication(context)
    , process_{path_to_application}
    , stdout_pipe_{context.asioContext().get_executor(), process_.stdoutPipe()}
    , stderr_pipe_{context.asioContext().get_executor(), process_.stderrPipe()}
{
    do_read();
}

ProcessApplication::~ProcessApplication() = default;

void ProcessApplication::do_read()
{
    stdout_pipe_.async_read_some(asio::buffer(buffer_), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            LOG_DEBUG(process_application_logger, "stdout: {}", std::string_view{buffer_.begin(), length});
            do_read();
        }
    });

    stderr_pipe_.async_read_some(asio::buffer(buffer_), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            LOG_DEBUG(process_application_logger, "stderr: {}", std::string_view{buffer_.begin(), length});
            do_read();
        }
    });
}
} // namespace quite
