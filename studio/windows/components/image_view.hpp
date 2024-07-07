#pragma once
#include <SDL_render.h>
#include <imgui.h>
#include "object_tree.hpp"

namespace quite::studio
{
class ImageView
{
  public:
    explicit ImageView(ObjectTree &tree, SDL_Renderer *renderer);
    ~ImageView();
    void draw();
    void higlight_object(const ObjectTree::ObjectNode *object);

  private:
    void fetch_image();

  private:
    struct AsyncImage
    {
        SDL_Renderer *renderer;
        bool dirty{false};
        Image image;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{nullptr, SDL_DestroyTexture};
        ImVec2 size;

        ImVec2 start_point_;
        ImVec2 end_point_;

        void show();
    };
    ObjectTree &tree_;
    exec::async_scope scope_;
    AsyncImage image_;
};

} // namespace quite::studio
