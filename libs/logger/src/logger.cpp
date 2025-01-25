#include <quill/Backend.h>
#include <quill/Frontend.h>
#include <quill/sinks/ConsoleSink.h>
#include <quill/sinks/FileSink.h>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>

namespace quite
{
quill::Logger *create_logger(std::string_view logger_name)
{
    try
    {
        auto default_sink = quill::Frontend::get_sink("default_sink");
        auto &&logger = quill::Frontend::create_or_get_logger(std::string{logger_name}, std::move(default_sink));
        logger->set_log_level(quill::LogLevel::Debug);

        return logger;
    }
    catch (const quill::QuillError &ex)
    {
        auto default_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("default_sink");
        auto &&logger = quill::Frontend::create_or_get_logger(std::string{logger_name}, std::move(default_sink));
        logger->set_log_level(quill::LogLevel::Debug);

        LOG_CRITICAL(logger, "Did you forget to call quite::setup_logger()? Error: {}", ex.what());

        return logger;
    }
}

void setup_logger(bool log_to_file)
{
    quill::Backend::start();
    quill::Frontend::preallocate();
    auto default_sink = [log_to_file]() {
        if (log_to_file)
        {
            return quill::Frontend::create_or_get_sink<quill::FileSink>(
                "default_sink",
                []() {
                    quill::FileSinkConfig cfg;
                    cfg.set_open_mode('w');
                    // cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
                    return cfg;
                }(),
                quill::FileEventNotifier{});
        }
        return quill::Frontend::create_or_get_sink<quill::ConsoleSink>("default_sink");
    }();
    auto &&logger = quill::Frontend::create_or_get_logger("root", std::move(default_sink));
    logger->set_log_level(quill::LogLevel::Debug);

    LOG_INFO(logger, "logging finished setup");
}

} // namespace quite
