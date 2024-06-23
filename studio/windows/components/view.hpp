#pragma once
#include <SDL_render.h>
#include <exec/async_scope.hpp>
#include <imgui.h>
#include <quite/application.hpp>
namespace quite::studio
{
class View
{
  public:
    explicit View(SDL_Renderer *renderer, std::shared_ptr<RemoteObject> view);
    ~View();

    void draw();

  private:
    void fetch_properties();
    void fetch_image();

  private:
    SDL_Renderer *renderer_;
    std::shared_ptr<RemoteObject> view_;
    exec::async_scope scope_;

    struct AsyncImage
    {
        SDL_Renderer *renderer;
        bool dirty{false};
        Image image;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{nullptr, SDL_DestroyTexture};
        ImVec2 size;

        void show();
    };
    AsyncImage image_;
};
} // namespace quite::studio
