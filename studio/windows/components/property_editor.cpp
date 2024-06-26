#include "property_editor.hpp"
#include <algorithm>
#include <ranges>
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
class PropertyEditor::PropertyUi
{
  public:
    ~PropertyUi() = default;
    virtual void draw() {};
};

class PropertyPrimitiveValue final : public PropertyEditor::PropertyUi
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
        void operator()(const std::shared_ptr<RemoteObject> &value) const noexcept
        {
            ImGui::Text("%s", "BUG: this should be a PropertyObjectValue");
        }
    };

  public:
    explicit PropertyPrimitiveValue(std::shared_ptr<Property> property)
        : property_{std::move(property)}
    {}

    void draw() override
    {
        ImGui::PushID(property_.get());
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        constexpr ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
        ImGui::TreeNodeEx("Field", flags, "%s", property_->name().c_str());

        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        if (property_->value().has_value())
        {
            std::visit(PropertyValueVisitor{}, property_->value().value());
        }
        ImGui::NextColumn();
        ImGui::PopID();
    }

  private:
    std::shared_ptr<Property> property_;
};

class PropertyObjectValue final : public PropertyEditor::PropertyUi
{
  public:
    explicit PropertyObjectValue(std::string name, std::shared_ptr<RemoteObject> object, bool initial_fetch = false)
        : name_{std::move(name)}
        , object_{std::move(object)}
    {
        if (initial_fetch)
        {
            fetch_properties();
        }
    }

    ~PropertyObjectValue()
    {
        auto wait_senders = scope_.on_empty();
        stdexec::sync_wait(wait_senders);
    }

    void draw() override;

  private:
    void fetch_properties();

  private:
    exec::async_scope scope_;
    std::string name_;
    std::shared_ptr<RemoteObject> object_;
    std::unordered_map<std::string, std::shared_ptr<PropertyUi>> properties_;
};

PropertyEditor::PropertyEditor(std::shared_ptr<RemoteObject> root)
    : root_{std::make_unique<PropertyObjectValue>("Root", std::move(root), true)}
{}

PropertyEditor::~PropertyEditor()
{}

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

        root_->draw();

        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
}

void PropertyObjectValue::draw()
{
    ImGui::PushID(object_.get());

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to
    // make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    const bool node_open = ImGui::TreeNode("Object", "%s", name_.c_str());
    if (node_open)
    {
        if (ImGui::Button("Fetch"))
        {
            fetch_properties();
        }
        ImGui::SameLine();
        for (auto &&prop : properties_)
        {
            prop.second->draw();
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

namespace
{
std::pair<std::string, std::shared_ptr<quite::studio::PropertyEditor::PropertyUi>> make_property_wrapper(
    const std::pair<std::string, std::shared_ptr<quite::Property>> &p)
{
    if (std::holds_alternative<std::shared_ptr<RemoteObject>>(p.second->value().value()))
    {
        return {p.first,
                std::make_shared<PropertyObjectValue>(
                    p.first, std::get<std::shared_ptr<RemoteObject>>(p.second->value().value()))};
    }
    return {p.first, std::make_shared<PropertyPrimitiveValue>(p.second)};
}
} // namespace

void PropertyObjectValue::fetch_properties()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](PropertyObjectValue *self) -> exec::task<void> {
        SPDLOG_LOGGER_DEBUG(logger_comp_prop_editor(), "Fetching properties...");
        auto props = co_await self->object_->fetch_properties({});
        if (props.has_value())
        {
            const auto insert_property = [self](auto &&prop_ui) { self->properties_.insert(std::move(prop_ui)); };
            std::ranges::for_each(props.value() | std::views::transform(make_property_wrapper), insert_property);
        }
        else
        {
            SPDLOG_LOGGER_ERROR(logger_comp_prop_editor(), "Could not fetch properties");
        }
        co_return;
    }(this)));
}
} // namespace quite::studio
