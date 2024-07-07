#include "element_tree_view.hpp"
#include <exec/async_scope.hpp>
#include <imgui.h>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>

namespace
{
LOGGER_IMPL(element_tree)
}

namespace quite::studio
{

ElementTreeView::ElementTreeView(ObjectTree &tree, PropertyEditor &property_editor, ImageView &image_view)
    : tree_{tree}
    , property_editor_{property_editor}
    , image_view_{image_view}
{}

ElementTreeView::~ElementTreeView() = default;

void ElementTreeView::draw()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    if (ImGui::BeginTable("##element_tree", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("Object");
        ImGui::TableHeadersRow();

        draw_tree_node(*tree_.root());

        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
}

void ElementTreeView::draw_tree_node(const ObjectTree::ObjectNode &node)
{

    auto obj_name =
        node.properties.contains("objectName")
            ? std::get<std::string>(node.properties.at("objectName")->value().value_or(Value{std::string{""}}))
            : std::string{""};
    if (obj_name.empty())
    {
        obj_name = "unknown"; //! TODO: replace with TypeName
    }

    ImGui::PushID(&node);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to
    // make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();

    constexpr ImGuiTreeNodeFlags kDefaultFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    constexpr ImGuiTreeNodeFlags kLeafFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    const auto node_flags = (node.leafs.empty() ? kLeafFlags : kDefaultFlags);

    const bool is_selected = (&node == current_);
    const bool node_open = ImGui::TreeNodeEx(
        "Object", (is_selected ? (node_flags | ImGuiTreeNodeFlags_Selected) : node_flags), "%s", obj_name.c_str());
    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    {
        current_ = &node;
        property_editor_.set_root(current_->object);
        image_view_.higlight_object(current_);
    }
    if (node_open and ((node_flags & ImGuiTreeNodeFlags_Leaf) == 0))
    {
        ImGui::SameLine();
        for (auto &&child : node.leafs)
        {
            draw_tree_node(*child);
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

} // namespace quite::studio
