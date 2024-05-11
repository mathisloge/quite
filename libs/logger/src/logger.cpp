#include <quite/create_logger.hpp>
#include <spdlog/spdlog.h>
namespace quite
{
std::shared_ptr<spdlog::logger> create_logger(std::string_view logger_name)
{
    auto logger = std::make_shared<spdlog::logger>(std::string{logger_name});
    logger->set_level(spdlog::default_logger()->level());
    logger->sinks() = spdlog::default_logger()->sinks();
    spdlog::register_logger(logger);

    return logger;
}
} // namespace quite
