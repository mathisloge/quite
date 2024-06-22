#include "quite/application.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "context.hpp"
#include "process_application.hpp"
namespace
{
LOGGER_IMPL(application)
}
namespace quite
{

Application::Application() = default;
Application::~Application() = default;

void Application::test()
{
    SPDLOG_LOGGER_DEBUG(logger_application(), "TEST");
}

std::shared_ptr<Application> Application::CreateApplication(const std::string &path_to_application)
{
    return std::make_shared<ProcessApplication>(Context::Instance(), path_to_application);
}
} // namespace quite
