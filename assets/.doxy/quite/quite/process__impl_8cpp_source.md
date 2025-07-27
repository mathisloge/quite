

# File process\_impl.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**src**](dir_acad3136c8ed89325e9252603ad8366c.md) **>** [**process\_impl.cpp**](process__impl_8cpp.md)

[Go to the documentation of this file](process__impl_8cpp.md)


```C++
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
```


