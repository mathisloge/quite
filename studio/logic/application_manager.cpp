#include "application_manager.hpp"
namespace quite::studio
{

void ApplicationManager::addApplication(const std::string &application)
{
    applications_.emplace_back(Application::CreateApplication(application));
}
} // namespace quite::studio
