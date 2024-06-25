#include "property_editor.hpp"
#include <imgui.h>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "scheduler.hpp"

namespace
{
LOGGER_IMPL(comp_prop_editor)
}

namespace quite::studio
{
PropertyEditor::PropertyEditor(std::shared_ptr<RemoteObject> root)
    : root_{std::move(root)}
{
    fetch_root_properties();
}

PropertyEditor::~PropertyEditor()
{
    auto wait_senders = scope_.on_empty();
    stdexec::sync_wait(wait_senders);
}

void PropertyEditor::draw()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    if (ImGui::BeginTable(
            "##property_editor", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("Object");
        ImGui::TableSetupColumn("Value");
        ImGui::TableHeadersRow();

        draw_object(*root_);

        // Iterate placeholder objects (all the same data)
        // for (int obj_i = 0; obj_i < 4; obj_i++)
        //    ShowPlaceholderObject("Object", obj_i);
        //
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
}

namespace
{
struct PropertyValueVisitor final
{
    void operator()(std::int64_t value) const noexcept
    {
        ImGui::Text("%lu", value);
    }
    void operator()(double value) const noexcept
    {
        ImGui::InputDouble("##value", &value);
    }
    void operator()(bool value) const noexcept
    {
        ImGui::Checkbox("##value", &value);
    }
    void operator()(const std::string &value) const noexcept
    {
        ImGui::Text("%s", value.c_str());
    }
};
} // namespace

void PropertyEditor::draw_object(RemoteObject &object)
{
    ImGui::PushID(&object);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to
    // make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    const bool node_open = ImGui::TreeNode("Object", "%s_%lu", "", reinterpret_cast<uint64_t>(&object));
    if (node_open)
    {
        for (auto &&prop : root_properties_)
        {
            draw_property(*prop.second);
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

void PropertyEditor::draw_property(Property &property)
{
    ImGui::PushID(&property);
    /*
    if(complex_unit) {
        draw_property();
    } else {
    */
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx("Field", flags, "%s", property.name().c_str());

    ImGui::TableSetColumnIndex(1);
    ImGui::SetNextItemWidth(-FLT_MIN);
    if (property.value().has_value())
    {
        std::visit(PropertyValueVisitor{}, property.value().value());
    }
    ImGui::NextColumn();
    /*
    }
    */
    ImGui::PopID();
}

void PropertyEditor::fetch_root_properties()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](PropertyEditor *self) -> exec::task<void> {
        SPDLOG_LOGGER_DEBUG(logger_comp_prop_editor(), "Fetching properties...");
        auto props = co_await self->root_->fetch_properties({});
        if (props.has_value())
        {
            self->root_properties_ = std::move(props.value());
        }
        else
        {
            SPDLOG_LOGGER_ERROR(logger_comp_prop_editor(), "Could not fetch properties");
        }
        co_return;
    }(this)));
}
} // namespace quite::studio
