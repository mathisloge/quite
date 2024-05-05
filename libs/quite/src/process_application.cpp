#include "process_application.hpp"
#include <spawn.h>
#include <spdlog/spdlog.h>
namespace quite
{
ProcessApplication::ProcessApplication(Context &context, const std::string &path_to_application)
    : process_{path_to_application}
    , stdout_pipe_{context.ioContext(), process_.stdoutPipe()}
    , stderr_pipe_{context.ioContext(), process_.stderrPipe()}
    , object_client_{context.grpcContext()}
{
    do_read();
}

ProcessApplication::~ProcessApplication() = default;

asio::awaitable<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> ProcessApplication::find_object(std::string_view object_name)
{
    co_return co_await object_client_.findObject();
}

void ProcessApplication::do_read()
{
    spdlog::trace("do_read");
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
            spdlog::debug("err {}", std::string_view{buffer.begin(), length});
            do_read();
        }
    });
}
} // namespace quite
