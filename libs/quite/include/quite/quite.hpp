#pragma once
#include <boost/asio/any_io_executor.hpp>
#include "asio2exec.hpp"
#include "quite/quite_client_export.hpp"

namespace quite
{
QUITE_CLIENT_EXPORT boost::asio::any_io_executor globalExecutor();
QUITE_CLIENT_EXPORT asio2exec::asio_context &asio_context();
} // namespace quite
