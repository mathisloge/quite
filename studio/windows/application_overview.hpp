#pragma once
#include <SDL_render.h>
#include <exec/async_scope.hpp>
#include <quite/application.hpp>
#include "components/view.hpp"

namespace quite::studio
{
class ApplicationOverview final
{
  public:
    ApplicationOverview(SDL_Renderer *renderer, std::shared_ptr<Application> application);
    ~ApplicationOverview();

    void drawWindow();

  private:
    void fetchViews();

  private:
    SDL_Renderer *renderer_;
    std::shared_ptr<Application> application_;
    bool window_open_{false};

    exec::async_scope scope_;

    bool fetch_in_progress_{false};
    std::unordered_map<ObjectId, std::unique_ptr<View>> views_;
};

} // namespace quite::studio
