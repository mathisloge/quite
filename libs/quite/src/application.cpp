#include "quite/application.hpp"
#include "process_application.hpp"

namespace quite
{

Application::~Application() = default;

std::shared_ptr<Application> Application::createApplication(const std::string &path_to_application)
{
    return std::make_shared<ProcessApplication>(path_to_application);
}
} // namespace quite
