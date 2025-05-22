#pragma once
#include <execpools/asio/asio_thread_pool.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{
QUITE_CORE_EXPORT execpools::asio_thread_pool &thread_pool();
QUITE_CORE_EXPORT auto get_executor() -> decltype(thread_pool().executor());

} // namespace quite
