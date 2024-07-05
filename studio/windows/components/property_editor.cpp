#include "property_editor.hpp"
#include <algorithm>
#include <map>
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

struct PropertyValueVisitor final
{
    void operator()(auto && /*value*/) const noexcept
    {
        ImGui::Text("%s", "BUG: this should not be a PropertyPrimitiveValue");
    }
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
class PropertyEditor::PropertyUi
{
  public:
    PropertyUi() = default;
    virtual ~PropertyUi() = default;
    virtual void draw() {};
};

class SimplePrimitiveValue final : public PropertyEditor::PropertyUi
{
  public:
    explicit SimplePrimitiveValue(std::string name, Value value)
        : name_{std::move(name)}
        , value_{std::move(value)}
    {}

    void draw() override
    {
        ImGui::PushID(this);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        constexpr ImGuiTreeNodeFlags kFlags =
            ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
        ImGui::TreeNodeEx("Field", kFlags, "%s", name_.c_str());

        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        std::visit(PropertyValueVisitor{}, value_);
        ImGui::NextColumn();
        ImGui::PopID();
    }

  private:
    std::string name_;
    Value value_;
};

class PropertyPrimitiveValue final : public PropertyEditor::PropertyUi
{
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
    std::map<std::string, std::shared_ptr<PropertyUi>> properties_;
};

class PropertyArrayValue final : public PropertyEditor::PropertyUi
{
  public:
    explicit PropertyArrayValue(std::string name, std::shared_ptr<Property> property, bool initial_fetch = false)
        : name_{std::move(name)}
        , property_{std::move(property)}
    {
        if (initial_fetch)
        {
            fetch_properties();
        }
    }

    ~PropertyArrayValue()
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
    std::shared_ptr<Property> property_;
    std::vector<std::unique_ptr<PropertyUi>> properties_;
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
    if (std::holds_alternative<xyz::indirect<ArrayObject>>(p.second->value().value()) or
        std::holds_alternative<xyz::indirect<ClassObject>>(p.second->value().value()))
    {
        return {p.first, std::make_shared<PropertyArrayValue>(p.first, p.second, true)};
    }
    return {p.first, std::make_shared<PropertyPrimitiveValue>(p.second)};
}

std::unique_ptr<quite::studio::PropertyEditor::PropertyUi> make_value_wrapper(std::string name, const Value &value)
{
    if (std::holds_alternative<std::shared_ptr<RemoteObject>>(value))
    {
        auto obj = std::get<std::shared_ptr<RemoteObject>>(value);
        return std::make_unique<PropertyObjectValue>(std::move(name), obj);
    }
    return std::make_unique<SimplePrimitiveValue>(std::move(name), value);
}
} // namespace

void PropertyObjectValue::fetch_properties()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](PropertyObjectValue *self) -> exec::task<void> {
        auto props = co_await self->object_->fetch_properties({});
        SPDLOG_LOGGER_DEBUG(logger_comp_prop_editor(), "Got properties.");
        if (props.has_value())
        {
            self->properties_.clear();
            const auto insert_property = [self](auto &&prop_ui) {
                self->properties_.insert(std::forward<decltype(prop_ui)>(prop_ui));
            };
            std::ranges::for_each(props.value() | std::views::filter([](auto &&prop_pair) {
                                      return prop_pair.second->value().has_value();
                                  }) | std::views::transform(make_property_wrapper),
                                  insert_property);
        }
        else
        {
            SPDLOG_LOGGER_ERROR(logger_comp_prop_editor(), "Could not fetch properties");
        }
        co_return;
    }(this)));
}

void PropertyArrayValue::draw()
{
    ImGui::PushID(property_.get());

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to
    // make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    const bool node_open = ImGui::TreeNode("Array", "%s", name_.c_str());
    if (node_open)
    {
        if (ImGui::Button("Fetch"))
        {
            fetch_properties();
        }
        ImGui::SameLine();
        for (auto &&prop : properties_)
        {
            prop->draw();
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

void PropertyArrayValue::fetch_properties()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](PropertyArrayValue *self) -> exec::task<void> {
        auto values = co_await self->property_->read();

        auto ui_elements = values.transform([](auto &&value) -> Result<std::vector<std::unique_ptr<PropertyUi>>> {
            if (std::holds_alternative<xyz::indirect<ArrayObject>>(value))
            {
                std::vector<std::unique_ptr<PropertyUi>> ui;
                const auto &values = (*std::get<xyz::indirect<ArrayObject>>(value)).values;
                ui.reserve(values.size());

                for (auto &&[index, v] : std::views::enumerate(values))
                {
                    ui.emplace_back(make_value_wrapper(std::format("[{}]", index), std::move(v)));
                }
                return ui;
            }
            if (std::holds_alternative<xyz::indirect<ClassObject>>(value))
            {
                std::vector<std::unique_ptr<PropertyUi>> ui;
                const auto &class_obj = (*std::get<xyz::indirect<ClassObject>>(value));
                ui.reserve(class_obj.members.size());
                for (auto &&[index, member] : std::views::enumerate(class_obj.members))
                {
                    ui.emplace_back(make_value_wrapper(std::move(member.name), std::move(member.value)));
                }
                return ui;
            }
            return std::unexpected{
                Error{.code = ErrorCode::invalid_argument, .message = "Expected an array or class type"}};
        });
        if (ui_elements->has_value())
        {
            self->properties_ = std::move(ui_elements->value());
        }
        else
        {
            SPDLOG_LOGGER_ERROR(
                logger_comp_prop_editor(), "Could not fetch props due to {}", ui_elements->error().message);
        }
        co_return;
    }(this)));
}
} // namespace quite::studio
