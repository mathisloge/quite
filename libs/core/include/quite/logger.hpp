#pragma once
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include "quite/quite_core_export.hpp"

namespace quite
{
QUITE_CORE_EXPORT quill::Logger *create_logger(std::string_view logger_name);
}

#define DEFINE_LOGGER(name)                                                                                            \
    namespace                                                                                                          \
    {                                                                                                                  \
    auto name()                                                                                                        \
    {                                                                                                                  \
        static const auto &&name_logger = ::quite::create_logger(#name);                                               \
        return name_logger;                                                                                            \
    }                                                                                                                  \
    }
