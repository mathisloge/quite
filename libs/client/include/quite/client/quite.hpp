#pragma once
#include <boost/asio/any_io_executor.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include "quite/quite_client_export.hpp"

namespace quite::client
{
QUITE_CLIENT_EXPORT execpools::asio_thread_pool &asio_context();
} // namespace quite
