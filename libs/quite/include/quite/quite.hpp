#pragma once
#include <asio/any_io_executor.hpp>
#include <asio/executor.hpp>
#include "quitelib_export.h"

namespace quite
{
QUITELIB_EXPORT asio::any_io_executor globalExecutor();
}
