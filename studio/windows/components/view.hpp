#pragma once
#include <SDL_render.h>
#include <exec/async_scope.hpp>
#include <imgui.h>
#include <quite/application.hpp>
#include "property_editor.hpp"
#include "element_tree_view.hpp"
namespace quite::studio
{
class View final
{
  public:
    explicit View(SDL_Renderer *renderer, const std::shared_ptr<RemoteObject> &view);
    ~View();

    void draw();

  private:
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

    PropertyEditor prop_editor_;
    ElementTreeView element_view_;
};
} // namespace quite::studio
