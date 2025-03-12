#include "process_impl.hpp"
#include <quite/asio2exec.hpp>

using boost::system::error_code;
namespace quite::manager
{
ProcessImpl::ProcessImpl(boost::process::v2::process &&process)
    : process_{std::move(process)}
{}

bool ProcessImpl::is_running()
{
    error_code ec;
    return process_.running(ec);
}

int ProcessImpl::exit_code()
{
    return process_.exit_code();
}

AsyncResult<int> ProcessImpl::async_wait_exit()
{
    auto [ec, code] = co_await process_.async_wait(asio2exec::use_sender);
    if (ec)
    {
        co_return make_error_result<int>(ErrorCode::aborted, ec.message());
    }
    co_return exit_code();
}

Result<void> ProcessImpl::request_exit()
{
    error_code ec;
    process_.request_exit(ec);
    return {};
}

Result<void> ProcessImpl::terminate()
{
    error_code ec;
    process_.terminate(ec);
    return {};
}

} // namespace quite::manager
