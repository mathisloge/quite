#pragma once
#include <memory>
#include <spdlog/fwd.h>
#include "loggerlib_export.h"
namespace quite
{
LOGGERLIB_EXPORT std::shared_ptr<spdlog::logger> create_logger(std::string_view logger_name);
}
