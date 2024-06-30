#pragma once
#include <quite/application.hpp>
#include "../windows/application_overview.hpp"
namespace quite::studio
{

class ApplicationManager
{
  public:
    explicit ApplicationManager(SDL_Renderer *renderer);
    void addApplication(const std::string &application);
    void draw();

  private:
    SDL_Renderer *renderer_;
    std::vector<std::shared_ptr<Application>> applications_;
    std::vector<std::unique_ptr<ApplicationOverview>> overviews_;
};
} // namespace quite::studio
