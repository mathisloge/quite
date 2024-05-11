#pragma once
#include <spdlog/fwd.h>

#define LOGGER_DEF(name) const std::shared_ptr<spdlog::logger> &logger_##name();

#define LOGGER_IMPL(name)                                                                                              \
    const std::shared_ptr<spdlog::logger> &logger_##name()                                                             \
    {                                                                                                                  \
        static auto ins_##name = ::quite::create_logger(#name);                                                        \
        return ins_##name;                                                                                             \
    }
