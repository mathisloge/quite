#include "view.hpp"
#include <imgui.h>

namespace quite::studio
{
View::View(SDL_Renderer *renderer, const std::shared_ptr<RemoteObject> &view)
    : renderer_{renderer}
    , view_{view}
    , tree_{view}
    , prop_editor_{view}
    , image_view_{tree_, renderer_}
    , element_view_{tree_, prop_editor_, image_view_} {};

View::~View() = default;

void View::draw()
{
    ImGui::BeginChild("visual tree", ImVec2{350, 0}, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
    element_view_.draw();
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("property_view", ImVec2(150, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
    prop_editor_.draw();
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::BeginChild("display view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), ImGuiChildFlags_Border);
    image_view_.draw();
    ImGui::EndChild();
    ImGui::EndGroup();
}
} // namespace quite::studio
