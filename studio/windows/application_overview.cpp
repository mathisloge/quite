#include "application_overview.hpp"
#include <exec/static_thread_pool.hpp>
#include <exec/task.hpp>
#include <imgui.h>
#include <quite/logger.hpp>
#include "../logic/scheduler.hpp"

DEFINE_LOGGER(application_overview);

namespace quite::studio
{
ApplicationOverview::ApplicationOverview(std::shared_ptr<Application> application)
    : application_(std::move(application))
{
    fetchViews();
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
    constexpr ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyScroll;
    if (ImGui::BeginTabBar("ViewsList", tab_bar_flags))
    {
        for (auto &&view : views_)
        {
            // todo: cache this one
            const auto label = fmt::format("View {}", view.first);
            if (ImGui::BeginTabItem(label.c_str()))
            {
                view.second->draw();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    if (fetch_in_progress_)
    {
        ImGui::Text("Loading views...");
    }
    ImGui::End();
}

void ApplicationOverview::fetchViews()
{
    scope_.spawn(stdexec::starts_on(get_scheduler(), [](ApplicationOverview *self) -> exec::task<void> {
        LOG_DEBUG(application_overview(), "Fetching views...");
        self->fetch_in_progress_ = true;
        auto view_result = co_await self->application_->get_views();
        if (view_result.has_value())
        {
            LOG_DEBUG(application_overview(), "got views");
            for (auto &&v : *view_result)
            {
                // self->views_[v->id()] = std::make_unique<View>(self->renderer_, v);
            }
        }
        else
        {
            LOG_ERROR(application_overview(), "Failed to get views: {}", view_result.error().message);
        }
        self->fetch_in_progress_ = false;
        co_return;
    }(this)));
}
} // namespace quite::studio
