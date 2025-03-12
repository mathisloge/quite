#include "noop_process.hpp"

namespace quite::manager
{
bool NoopProcess::is_running()
{
    return true;
}

int NoopProcess::exit_code()
{
    return EXIT_SUCCESS;
}

AsyncResult<int> NoopProcess::async_wait_exit()
{
    co_return exit_code();
}

Result<void> NoopProcess::request_exit()
{
    return {};
}

Result<void> NoopProcess::terminate()
{
    return {};
}

} // namespace quite::manager
