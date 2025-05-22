#include "process_impl.hpp"
#include <asioexec/use_sender.hpp>

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
    auto exit_code = co_await process_.async_wait(asioexec::use_sender);
    co_return exit_code;
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
