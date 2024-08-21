#pragma once
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include "loggerlib_export.h"

namespace quite
{
LOGGERLIB_EXPORT quill::Logger *create_logger(std::string_view logger_name);
}

#define DEFINE_LOGGER(name)                                                                                            \
    namespace                                                                                                          \
    {                                                                                                                  \
    const auto &&name = ::quite::create_logger(#name);                                                                 \
    }
