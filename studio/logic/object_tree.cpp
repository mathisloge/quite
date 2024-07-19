#include "object_tree.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "scheduler.hpp"

namespace
{
LOGGER_IMPL(object_tree)

constexpr std::string_view kContentItemKey = "contentItem";
constexpr std::string_view kChildrenKey = "children";
} // namespace

namespace quite::studio
{

ObjectTree::ObjectTree(RemoteObjectPtr root)
    : root_{std::make_shared<ObjectNode>(std::move(root))}
{
    init_from_properties(root_);
}

ObjectTree::~ObjectTree()
{
    auto wait_senders = scope_.on_empty();
    stdexec::sync_wait(wait_senders);
}

const ObjectTree::ObjectNodePtr &ObjectTree::root() const
{
    return root_;
}

void ObjectTree::init_from_properties(const ObjectNodePtr &node)
{
    scope_.spawn(stdexec::on(get_scheduler(), [](ObjectTree *self, ObjectNodePtr node) -> exec::task<void> {
        auto properties = co_await node->object->fetch_properties({});

        if (properties.has_value())
        {
            node->properties = std::move(properties.value());
            self->construct_node_from_properties(node);
        }
        else
        {
            SPDLOG_LOGGER_ERROR(
                logger_object_tree(), "Could not fetch properties. Failed with {}", properties.error().message);
        }
    }(this, node)));
}

void ObjectTree::construct_node_from_properties(const ObjectNodePtr &node)
{
    if (node->properties.contains(kContentItemKey.data()))
    {
        auto child = create_from_property(node->properties.at(kContentItemKey.data()));
        if (child != nullptr)
        {
            init_from_properties(child);
            node->leafs.emplace_back(std::move(child));
        }
    }
    else if (node->properties.contains(kChildrenKey.data()))
    {
        auto childs = node->properties.at(kChildrenKey.data());
        if (not childs->value().has_value())
        {
            SPDLOG_LOGGER_ERROR(logger_object_tree(),
                                "property {} does not contain any value. Value error: {}",
                                childs->name(),
                                childs->value().error().message);
            return;
        }

        auto &&value = childs->value().value();
        if (not std::holds_alternative<xyz::indirect<ArrayObject>>(value))
        {
            SPDLOG_LOGGER_ERROR(logger_object_tree(), "property {} does not contain a array value.", childs->name());
            return;
        }

        auto &&child_objs = std::get<xyz::indirect<ArrayObject>>(value);
        for (auto &&child_node :
             child_objs->values |                                                                         //
                 std::views::transform([this](const Value &value) { return create_from_value(value); }) | //
                 std::views::filter([](auto &&node) { return node != nullptr; }))
        {
            init_from_properties(child_node);
            child_node->parent = node;
            node->leafs.emplace_back(std::forward<decltype(child_node)>(child_node));
        }
    }
    else
    {
        SPDLOG_LOGGER_ERROR(logger_object_tree(),
                            "Could not create object from properties. Neither {} or {} present",
                            kContentItemKey,
                            kChildrenKey);
    }
}

ObjectTree::ObjectNodePtr ObjectTree::create_from_property(PropertyPtr property)
{
    if (not property->value().has_value())
    {
        SPDLOG_LOGGER_ERROR(logger_object_tree(),
                            "property {} does not contain any value. Value error: {}",
                            property->name(),
                            property->value().error().message);
        return nullptr;
    }

    auto &&value = property->value().value();
    return create_from_value(value);
}

ObjectTree::ObjectNodePtr ObjectTree::create_from_value(const Value &value)
{
    if (not std::holds_alternative<RemoteObjectPtr>(value))
    {
        SPDLOG_LOGGER_ERROR(logger_object_tree(), "value does not contain a remote object value.");
        return nullptr;
    }

    auto &&obj = std::get<RemoteObjectPtr>(value);
    return std::make_shared<ObjectTree::ObjectNode>(obj);
}
} // namespace quite::studio
