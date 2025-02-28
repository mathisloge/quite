#include "application_manager.hpp"
namespace quite::studio
{

ApplicationManager::ApplicationManager()
{}

void ApplicationManager::addApplication(const std::string &application)
{
    // const auto created_application = applications_.emplace_back(Application::CreateApplication(application));
    //  overviews_.emplace_back(std::make_unique<ApplicationOverview>(renderer_, created_application));
}

void ApplicationManager::draw()
{
    for (const auto &o : overviews_)
    {
        o->drawWindow();
    }
}
} // namespace quite::studio
