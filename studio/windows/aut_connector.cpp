#include "aut_connector.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

namespace
{
constexpr auto kConnectPopupId = "Connect...";
}
namespace quite::studio
{
AutConnector::AutConnector(std::shared_ptr<ApplicationManager> app_manager)
    : app_manager_{app_manager}
{}

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
    const bool address_accepted = ImGui::InputTextWithHint("Application address",
                                                           "unix:///tmp/grpc_probe.sock",
                                                           &tmp_connect_popup_input_,
                                                           ImGuiInputTextFlags_EnterReturnsTrue);

    if (ImGui::Button("Connect##Button") or address_accepted)
    {
        app_manager_->addApplication("" /*"/home/mathis/dev/ng-quite/build/test/simple_tester/tester"*/);
        ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
}
} // namespace quite::studio
