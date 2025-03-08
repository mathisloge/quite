#include "app.hpp"
#include <cmrc/cmrc.hpp>
#include <imgui.h>

CMRC_DECLARE(studiorc);
namespace quite::studio
{
App::App() = default;

void App::setup()
{
    load_fonts();
}

void App::load_fonts()
{
    ImGuiIO &io = ImGui::GetIO();
    auto fs = cmrc::studiorc::get_filesystem();

    ImFontConfig font_config{};
    font_config.FontDataOwnedByAtlas = false;

    auto sauce_code_pro_regular = fs.open("assets/fonts/SauceCodeProNerdFont-Regular.ttf");

    io.Fonts->AddFontFromMemoryTTF(
        (void *)sauce_code_pro_regular.begin(), sauce_code_pro_regular.size(), 18.0F, &font_config);
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
