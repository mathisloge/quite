#include "app.hpp"
#include <imgui.h>
#include <spdlog/spdlog.h>

namespace quite::studio
{

void App::show()
{
    showMainMenu();
    aut_connector_.connectPopup();
}

void App::showMainMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Applications"))
        {
            if (ImGui::MenuItem("Connect"))
            {
                spdlog::debug("connect");
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
