#include "process_application.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>

namespace
{
LOGGER_IMPL(process_application)
}

namespace quite
{
ProcessApplication::ProcessApplication(Context &context, const std::string &path_to_application)
    : GrpcApplication(context)
    , process_{path_to_application}
    , stdout_pipe_{context.asioContext().get_executor(), process_.stdoutPipe()}
    , stderr_pipe_{context.asioContext().get_executor(), process_.stderrPipe()}
{
    // do_read();
}

ProcessApplication::~ProcessApplication() = default;

void ProcessApplication::do_read()
{
    stdout_pipe_.async_read_some(asio::buffer(buffer_), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            spdlog::debug("out {}", std::string_view{buffer_.begin(), length});
            do_read();
        }
    });

    stderr_pipe_.async_read_some(asio::buffer(buffer_), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            spdlog::debug("err {}", std::string_view{buffer_.begin(), length});
            do_read();
        }
    });
}
} // namespace quite
