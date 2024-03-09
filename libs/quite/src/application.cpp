#include "quite/application.hpp"
#include "context.hpp"
#include "process_application.hpp"
namespace quite
{

Application::Application() = default;
Application::~Application() = default;

std::shared_ptr<Application> Application::CreateApplication(const std::string &path_to_application)
{
    return std::make_shared<ProcessApplication>(Context::Instance().ioContext(), path_to_application);
}
} // namespace quite
