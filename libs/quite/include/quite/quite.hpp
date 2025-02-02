#pragma once
#include <boost/asio/any_io_executor.hpp>
#include "quite/quite_client_export.hpp"

namespace quite
{
QUITE_CLIENT_EXPORT boost::asio::any_io_executor globalExecutor();
}
