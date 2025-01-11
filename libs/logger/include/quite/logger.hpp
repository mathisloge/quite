#pragma once
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include "quite_logger_export.h"

namespace quite
{
QUITE_LOGGER_EXPORT quill::Logger *create_logger(std::string_view logger_name);
}

#define DEFINE_LOGGER(name)                                                                                            \
    namespace                                                                                                          \
    {                                                                                                                  \
    const auto &&name = ::quite::create_logger(#name);                                                                 \
    }
