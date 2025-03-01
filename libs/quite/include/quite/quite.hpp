#pragma once
#include <boost/asio/any_io_executor.hpp>
#include <quite/asio2exec.hpp>
#include "quite/quite_client_export.hpp"

namespace quite
{
QUITE_CLIENT_EXPORT asio2exec::asio_context &asio_context();
} // namespace quite
