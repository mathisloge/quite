#pragma once
#include <asio/any_io_executor.hpp>
#include <asio/executor.hpp>
#include "quite/quite_client_export.hpp"

namespace quite
{
QUITE_CLIENT_EXPORT asio::any_io_executor globalExecutor();
}
