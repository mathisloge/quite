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
{}

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
                SPDLOG_LOGGER_DEBUG(logger_application_overview(), "GOT VIEWS");
                for (auto &&v : *view_result)
                {
                    self->views_[v->id()] = std::make_unique<View>(self->renderer_, v);
                }
            }
            else
            {
                SPDLOG_LOGGER_ERROR(
                    logger_application_overview(), "Failed to get views: {}", view_result.error().message);
            }
            co_return;
        }(this)));
    }

    constexpr ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyScroll;
    // ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyScroll;
    if (ImGui::BeginTabBar("ViewsList", tab_bar_flags))
    {
        for (auto &&view : views_)
        {
            // ImGui::PushID(view.second.get());
            const auto label = fmt::format("View {}", view.first);
            if (ImGui::BeginTabItem("View"))
            {
                view.second->draw();
                ImGui::EndTabItem();
            }

            // ImGui::PopID();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
} // namespace quite::studio
