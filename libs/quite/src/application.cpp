#include "quite/application.hpp"
#include "process_application.hpp"

namespace quite
{

Application::~Application() = default;

std::shared_ptr<Application> Application::createApplication(asio::io_context& io_context, const std::string &path_to_application)
{
    return std::make_shared<ProcessApplication>(io_context, path_to_application);
}
} // namespace quite
