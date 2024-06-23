#include "application_overview.hpp"
#include <SDL_surface.h>
#include <exec/static_thread_pool.hpp>
#include <exec/task.hpp>
#include <imgui.h>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "../logic/scheduler.hpp"

namespace
{
LOGGER_IMPL(application_overview)
}
namespace quite::studio
{
ApplicationOverview::ApplicationOverview(SDL_Renderer *renderer, std::shared_ptr<Application> application)
    : renderer_{renderer}
    , application_(std::move(application))
{
}

ApplicationOverview::~ApplicationOverview()
{
    auto wait_senders = scope_.on_empty();
    stdexec::sync_wait(wait_senders);
}

void ApplicationOverview::drawWindow()
{
    if (not ImGui::Begin("AppOverview", &window_open_))
    {
        ImGui::End();
        return;
    }
    if (ImGui::Button("Test"))
    {
        scope_.spawn(stdexec::on(get_scheduler(), [](ApplicationOverview *self) -> exec::task<void> {
            SPDLOG_LOGGER_DEBUG(logger_application_overview(), "Start");
            auto view_result = co_await self->application_->get_views();
            if (view_result.has_value())
            {
                SPDLOG_LOGGER_DEBUG(logger_application_overview(), "GOT VIEW");
                self->views_ = std::move(*view_result);
                co_await self->fetchImage();
            }
            else
            {
                SPDLOG_LOGGER_ERROR(
                    logger_application_overview(), "Failed to get views: {}", view_result.error().message);
            }
            co_return;
        }(this)));
    }
    for (auto &&view : views_)
    {
        ImGui::Text("Got view\n");
        if (tex_ == nullptr && img_)
        {
            auto image_data = img_->img.data();
            w = image_data.width;
            h = image_data.height;
            SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *)image_data.data.data(),
                                                            image_data.width,
                                                            image_data.height,
                                                            8 * image_data.channels,
                                                            image_data.channels * image_data.width,
                                                            0x000000ff,
                                                            0x0000ff00,
                                                            0x00ff0000,
                                                            0xff000000);

            tex_ = SDL_CreateTextureFromSurface(renderer_, surface);
            SDL_FreeSurface(surface);
        }
        if (tex_)
        {
            ImGui::Image((void *)tex_, ImVec2(w, h));
        }
    }
    ImGui::End();
}

exec::task<void> ApplicationOverview::fetchImage()
{
    SPDLOG_LOGGER_DEBUG(logger_application_overview(), "Get image for view");
    auto &&view = views_[0];

    auto snapshot = co_await view->take_snapshot();

    if (snapshot.has_value())
    {
        img_.reset(new ImgWrapper{std::move(snapshot.value())});
    }
    else
    {
        SPDLOG_LOGGER_ERROR(logger_application_overview(), "Failed to view image: {}", snapshot.error().message);
    }
}
} // namespace quite::studio
