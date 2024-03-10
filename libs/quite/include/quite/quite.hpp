#pragma once
#include "quitelib_export.h"
#include <asio/any_io_executor.hpp>
#include <asio/executor.hpp>

namespace quite
{
QUITELIB_EXPORT asio::any_io_executor globalExecutor();
}
