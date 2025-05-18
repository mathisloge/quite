#pragma once
#include "quite/asio_config.hpp"
#include "quite/quite_core_export.hpp"

namespace execpools
{
class asio_thread_pool;
}
namespace quite
{
QUITE_CORE_EXPORT void create_asio_context();
QUITE_CORE_EXPORT execpools::asio_thread_pool &thread_pool();
QUITE_CORE_EXPORT asio_impl::any_io_executor get_executor();

} // namespace quite
