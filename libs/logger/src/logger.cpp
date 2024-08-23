#include <quill/Backend.h>
#include <quill/Frontend.h>
#include <quill/sinks/ConsoleSink.h>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>

namespace quite
{
quill::Logger *create_logger(std::string_view logger_name)
{
    auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console_sink");

    auto &&logger = quill::Frontend::create_or_get_logger(logger_name.data(), std::move(console_sink));

    logger->set_log_level(quill::LogLevel::Debug);

    return logger;
}

void setup_logger()
{
    quill::Backend::start();
    quill::Frontend::preallocate();
}

} // namespace quite
