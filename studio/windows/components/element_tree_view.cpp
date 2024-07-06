#include "element_tree_view.hpp"
#include <algorithm>
#include <map>
#include <ranges>
#include <exec/async_scope.hpp>
#include <imgui.h>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "scheduler.hpp"

namespace
{
LOGGER_IMPL(element_tree)
}

namespace quite::studio
{

class ElementTreeView::TreeElement : public std::enable_shared_from_this<TreeElement>
{
  public:
    explicit TreeElement(ElementTreeView &cnt,
                         std::string name,
                         std::shared_ptr<RemoteObject> object,
                         bool initial_fetch = false)
        : cnt_{cnt}
        , name_{std::move(name)}
        , object_{std::move(object)}
    {
        if (initial_fetch)
        {
            fetch_properties();
        }
    }

    ~TreeElement()
    {
        auto wait_senders = scope_.on_empty();
        stdexec::sync_wait(wait_senders);
    }

    void draw();

  private:
    void fetch_properties();

    void set_as_selected_element()
    {
        cnt_.set_selected_element(shared_from_this());
    }

  private:
    ElementTreeView &cnt_;
    exec::async_scope scope_;
    std::string name_;
    std::shared_ptr<RemoteObject> object_;
    std::vector<std::shared_ptr<TreeElement>> childs_;
};

ElementTreeView::ElementTreeView(std::shared_ptr<RemoteObject> root)
    : root_{std::make_shared<TreeElement>(*this, "Root", std::move(root), true)}
    , current_{root_}
{}

ElementTreeView::~ElementTreeView() = default;

void ElementTreeView::draw()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    if (ImGui::BeginTable(
            "##element_tree", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
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

void ElementTreeView::set_selected_element(std::shared_ptr<TreeElement> element)
{
    current_ = std::move(element);
}

void ElementTreeView::TreeElement::fetch_properties()
{
    scope_.spawn(stdexec::on(get_scheduler(), [](TreeElement *self) -> exec::task<void> {
        auto props = co_await self->object_->fetch_properties({"contentItem", "children", "objectName"});
        SPDLOG_LOGGER_DEBUG(logger_element_tree(), "Got properties.");
        if (props.has_value())
        {
            self->childs_.clear();
            auto &&prop_map = props.value();

            auto obj_name =
                prop_map.contains("objectName")
                    ? std::get<std::string>(prop_map.at("objectName")->value().value_or(Value{std::string{""}}))
                    : std::string{""};
            if (obj_name.empty())
            {
                obj_name = "unknown"; //! TODO: replace with TypeName
            }

            if (prop_map.contains("contentItem"))
            {
                auto &&item = prop_map.at("contentItem");
                if (item->value().has_value() and std::holds_alternative<RemoteObjectPtr>(*item->value()))
                {
                    self->childs_.emplace_back(
                        std::make_shared<TreeElement>(self->cnt_, obj_name, std::get<RemoteObjectPtr>(*item->value())));
                }
            }
            if (prop_map.contains("children"))
            {
                auto &&prop_childs = prop_map.at("children");
                if (prop_childs->value().has_value() and
                    std::holds_alternative<xyz::indirect<ArrayObject>>(*prop_childs->value()))
                {
                    auto &&array_childs = std::get<xyz::indirect<ArrayObject>>(*prop_childs->value());
                    for (auto &&prop : array_childs->values)
                    {
                        if (std::holds_alternative<RemoteObjectPtr>(prop))
                        {
                            self->childs_.emplace_back(
                                std::make_shared<TreeElement>(self->cnt_, obj_name, std::get<RemoteObjectPtr>(prop)));
                        }
                    }
                }
            }
        }
        else
        {
            SPDLOG_LOGGER_ERROR(logger_element_tree(), "Could not fetch properties");
        }
        co_return;
    }(this)));
}

void ElementTreeView::TreeElement::draw()
{
    ImGui::PushID(object_.get());

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to
    // make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();

    const bool is_selected = (cnt_.current_.get() == this);
    const bool node_open = ImGui::TreeNodeEx(
        "Object", (is_selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None), "%s", name_.c_str());
    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    {
        SPDLOG_LOGGER_DEBUG(logger_element_tree(), "select item {}", reinterpret_cast<std::uint64_t>(this));
        set_as_selected_element();
    }
    if (node_open)
    {
        if (ImGui::Button("Fetch"))
        {
            fetch_properties();
        }
        ImGui::SameLine();
        for (auto &&prop : childs_)
        {
            prop->draw();
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}

} // namespace quite::studio
