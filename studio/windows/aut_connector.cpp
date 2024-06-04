#include "aut_connector.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

namespace
{
constexpr auto kConnectPopupId = "Connect...";
}
namespace quite::studio
{
void AutConnector::showConnectPopup()
{
    // id stack workaround
    do_connect_popup_ = true;
}

void AutConnector::connectPopup()
{
    if (do_connect_popup_)
    {
        do_connect_popup_ = false;
        ImGui::OpenPopup(kConnectPopupId);
    }

    if (not ImGui::BeginPopupModal(
            kConnectPopupId, nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
    {
        return;
    }
    const bool address_accepted = ImGui::InputTextWithHint(
        "Application address", "localhost:50051", &tmp_connect_popup_input_, ImGuiInputTextFlags_EnterReturnsTrue);

    if (ImGui::Button("Connect##Button") or address_accepted)
    {
        ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
}
} // namespace quite::studio
