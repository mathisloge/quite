#pragma once
#include <SDL_render.h>
#include <exec/async_scope.hpp>
#include <quite/application.hpp>
#include "components/view.hpp"
namespace quite::studio
{
struct ImgWrapper
{
    Image img;
};
class ApplicationOverview
{
  public:
    ApplicationOverview(SDL_Renderer *renderer, std::shared_ptr<Application> application);
    ~ApplicationOverview();

    void drawWindow();

  private:
    SDL_Renderer *renderer_;
    std::shared_ptr<Application> application_;
    bool window_open_{false};

    exec::async_scope scope_;

    std::unordered_map<ObjectId, std::unique_ptr<View>> views_;
    View *current_view_{nullptr};
};

} // namespace quite::studio
