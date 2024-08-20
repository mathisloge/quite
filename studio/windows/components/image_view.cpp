#include "image_view.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "scheduler.hpp"

namespace
{
LOGGER_IMPL(image_view)
}

namespace quite::studio
{
ImageView::ImageView(ObjectTree &tree, SDL_Renderer *renderer)
    : tree_{tree}
    , image_{renderer}
{
    fetch_image();
}

ImageView::~ImageView()
{
    auto wait_senders = scope_.on_empty();
    stdexec::sync_wait(wait_senders);
}

void ImageView::draw()
{
    if (ImGui::Button("Refresh image"))
    {
        fetch_image();
    }
    image_.show();
}

struct Value2NumberVisitor
{
    float operator()(auto &&val)
    {
        return 0.f;
    };

    float operator()(std::int64_t val)
    {
        return static_cast<float>(val);
    };

    float operator()(double val)
    {
        return static_cast<float>(val);
    };
};

void ImageView::higlight_object(const ObjectTree::ObjectNode *object)
{
    auto get_number_property = [](const std::unordered_map<std::string, PropertyPtr> &props,
                                  const std::string_view &prop_name) {
        auto &&prop = props.at(prop_name.data());
        return std::visit(Value2NumberVisitor{}, prop->value().value());
    };

    image_.start_point_.x = get_number_property(object->properties, "x");
    image_.start_point_.y = get_number_property(object->properties, "y");
    image_.end_point_.x = get_number_property(object->properties, "width");
    image_.end_point_.y = get_number_property(object->properties, "height");

    auto parent = object->parent;
    SPDLOG_LOGGER_DEBUG(logger_image_view(), "highlight object. has parent={}", (parent != nullptr));
    while (parent != nullptr)
    {
        image_.start_point_.x += get_number_property(parent->properties, "x");
        image_.start_point_.y += get_number_property(parent->properties, "y");
        SPDLOG_LOGGER_DEBUG(logger_image_view(), "highlight: x={} y={}", image_.start_point_.x, image_.start_point_.y);
        if (parent->position_root)
        {
            break;
        }
        parent = parent->parent;
    }
}

void ImageView::fetch_image()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](ImageView *self) -> exec::task<void> {
        auto snapshot_result = co_await self->tree_.root()->object->take_snapshot();
        SPDLOG_LOGGER_DEBUG(logger_image_view(), "got snapshot");
        if (snapshot_result.has_value())
        {
            self->image_.image = std::move(snapshot_result.value());
            self->image_.dirty = true;
        }
    }(this)));
}

void ImageView::AsyncImage::show()
{
    if (dirty)
    {
        auto image_data = image.data();
        size = ImVec2(image_data.width, image_data.height);
        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *)image_data.data.data(),
                                                        image_data.width,
                                                        image_data.height,
                                                        8 * image_data.channels,
                                                        image_data.channels * image_data.width,
                                                        0x000000ff,
                                                        0x0000ff00,
                                                        0x00ff0000,
                                                        0xff000000);

        texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
        SDL_FreeSurface(surface);
        dirty = false;
    }
    if (texture)
    {
        ImDrawList *draw_list = ImGui::GetWindowDrawList();
        const ImVec2 p = ImGui::GetCursorScreenPos();
        ImGui::Image((void *)texture.get(), size);

        constexpr auto kHighlightColor = ImColor{255, 0, 0};

        const auto p0 = ImVec2{p.x + start_point_.x, p.y + start_point_.y};
        const auto p1 = ImVec2{p0.x + end_point_.x, p0.y + end_point_.y};
        draw_list->AddRect(p0, p1, kHighlightColor);
    }
}
} // namespace quite::studio
