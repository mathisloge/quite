#include "view.hpp"
#include <imgui.h>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "scheduler.hpp"

namespace
{
LOGGER_IMPL(comp_view)
}

namespace quite::studio
{
View::View(SDL_Renderer *renderer, const std::shared_ptr<RemoteObject> &view)
    : renderer_{renderer}
    , view_{view}
    , image_{renderer_}
    , prop_editor_{view}
{
    fetch_image();
};

View::~View()
{
    auto wait_senders = scope_.on_empty();
    stdexec::sync_wait(wait_senders);
}

void View::draw()
{
    ImGui::BeginChild("property pane", ImVec2{350, 0}, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
    prop_editor_.draw();
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::BeginChild("display view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
    if (ImGui::Button("Refresh image"))
    {
        fetch_image();
    }
    image_.show();
    ImGui::EndChild();
    ImGui::EndGroup();
}

void View::fetch_image()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](View *self) -> exec::task<void> {
        auto snapshot_result = co_await self->view_->take_snapshot();
        SPDLOG_LOGGER_DEBUG(logger_comp_view(), "got snapshot");
        if (snapshot_result.has_value())
        {
            self->image_.image = std::move(snapshot_result.value());
            self->image_.dirty = true;
        }
    }(this)));
}

void View::AsyncImage::show()
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
        ImGui::Image((void *)texture.get(), size);
    }
}
} // namespace quite::studio
