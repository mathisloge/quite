#include "process_application.hpp"
#include <spawn.h>
#include <spdlog/spdlog.h>
namespace quite
{
ProcessApplication::ProcessApplication(asio::io_context &io_context, const std::string &path_to_application)
    : process_{path_to_application}
    , stdout_pipe_{io_context, process_.stdoutPipe()}
    , stderr_pipe_{io_context, process_.stderrPipe()}
{
    do_read();
}

ProcessApplication::~ProcessApplication()
{}

void ProcessApplication::do_read()
{
    spdlog::debug("do_read");
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
