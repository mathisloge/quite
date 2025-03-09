#include "application_impl.hpp"
#include <quite/asio2exec.hpp>

using boost::system::error_code;
namespace quite::manager
{
bool ApplicationImpl::is_running()
{
    error_code ec;
    return process_.running(ec);
}

int ApplicationImpl::exit_code()
{
    return process_.exit_code();
}

AsyncResult<int> ApplicationImpl::async_wait_exit()
{
    auto [ec, code] = co_await process_.async_wait(asio2exec::use_sender);
    if (ec)
    {
        co_return make_error_result<int>(ErrorCode::aborted, "");
    }
    co_return exit_code();
}

Result<void> ApplicationImpl::request_exit()
{
    error_code ec;
    process_.request_exit(ec);
    return {};
}

Result<void> ApplicationImpl::terminate()
{
    error_code ec;
    process_.terminate(ec);
    return {};
}

} // namespace quite::manager
