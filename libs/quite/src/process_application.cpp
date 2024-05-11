#include "process_application.hpp"
#include <spawn.h>
#include <spdlog/spdlog.h>
namespace quite
{
ProcessApplication::ProcessApplication(Context &context, const std::string &path_to_application)
    : process_{path_to_application}
    , stdout_pipe_{context.asioContext().get_executor(), process_.stdoutPipe()}
    , stderr_pipe_{context.asioContext().get_executor(), process_.stderrPipe()}
    , api_handle_{std::make_shared<ApiHandle>(context.grpcContext())}
{
    do_read();
}

ProcessApplication::~ProcessApplication() = default;

std::shared_ptr<ApiHandle> ProcessApplication::api_handle() const
{
    return api_handle_;
}

void ProcessApplication::do_read()
{
    // spdlog::trace("do_read");
    stdout_pipe_.async_read_some(asio::buffer(buffer), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            spdlog::debug("out {}", std::string_view{buffer.begin(), length});
            do_read();
        }
    });

    stderr_pipe_.async_read_some(asio::buffer(buffer), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            // spdlog::debug("err {}", std::string_view{buffer.begin(), length});
            do_read();
        }
    });
}
} // namespace quite
