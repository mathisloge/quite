#include "app.hpp"
#include <imgui.h>
#include <spdlog/spdlog.h>

namespace quite::studio
{
App::App(SDL_Renderer *renderer)
    : renderer_{renderer}
{
    spdlog::set_level(spdlog::level::debug);
}

void App::show()
{
    showMainMenu();
    aut_connector_.connectPopup();
    app_manager_->draw();
}

void App::showMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Applications"))
        {
            if (ImGui::MenuItem("Connect"))
            {
                aut_connector_.showConnectPopup();
            }
            if (ImGui::BeginMenu("Connect recent"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
} // namespace quite::studio
