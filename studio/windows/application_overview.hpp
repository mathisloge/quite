#pragma once
#include <SDL_render.h>
#include <quite/application.hpp>
#include <exec/async_scope.hpp>
namespace quite::studio
{
  struct ImgWrapper {
    Image img;
  };
class ApplicationOverview
{
  public:
    ApplicationOverview(SDL_Renderer* renderer, std::shared_ptr<Application> application);
    ~ApplicationOverview();

    void drawWindow();
private:
    exec::task<void> fetchImage();

  private:
  SDL_Renderer* renderer_;
    std::shared_ptr<Application> application_;
    bool window_open_{false};

    exec::async_scope scope_;
    std::vector<std::shared_ptr<RemoteObject>> views_;

    std::unique_ptr<ImgWrapper> img_{nullptr};
    SDL_Texture* tex_{nullptr};
    int w, h;
};


} // namespace quite::studio
