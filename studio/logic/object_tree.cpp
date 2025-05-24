#include "object_tree.hpp"
#include <quite/logger.hpp>
#include "scheduler.hpp"

DEFINE_LOGGER(logic_object_tree);

namespace
{
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
    scope_.spawn(stdexec::starts_on(get_scheduler(), [](ObjectTree *self, ObjectNodePtr node) -> exec::task<void> {
        auto properties = co_await node->object->fetch_properties({});

        if (properties.has_value())
        {
            node->properties = std::move(properties.value());
            self->construct_node_from_properties(node);
        }
        else
        {
            LOG_ERROR(logic_object_tree(), "Could not fetch properties. Failed with {}", properties.error().message);
        }
    }(this, node)));
}

void ObjectTree::construct_node_from_properties(const ObjectNodePtr &node)
{
    if (node->properties.contains(kContentItemKey.data()))
    {
        //! TODO: set root position for view to false
        node->position_root = true;
        auto child = create_from_property(node->properties.at(kContentItemKey.data()));
        if (child != nullptr)
        {
            init_from_properties(child);
            child->parent = node;
            node->leafs.emplace_back(std::move(child));
        }
    }
    else if (node->properties.contains(kChildrenKey.data()))
    {
        auto children = node->properties.at(kChildrenKey.data());
        if (not children->value().has_value())
        {
            LOG_ERROR(logic_object_tree(),
                      "property {} does not contain any value. Value error: {}",
                      children->name(),
                      children->value().error().message);
            return;
        }

        auto &&value = children->value().value();
        if (not std::holds_alternative<xyz::indirect<ArrayObject>>(value))
        {
            LOG_ERROR(logic_object_tree(), "property {} does not contain a array value.", children->name());
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
            node->leafs.emplace_back(child_node);
        }
    }
    else
    {
        LOG_ERROR(logic_object_tree(),
                  "Could not create object from properties. Neither {} or {} present",
                  kContentItemKey,
                  kChildrenKey);
    }
}

ObjectTree::ObjectNodePtr ObjectTree::create_from_property(PropertyPtr property)
{
    if (not property->value().has_value())
    {
        LOG_ERROR(logic_object_tree(),
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
        LOG_ERROR(logic_object_tree(), "value does not contain a remote object value.");
        return nullptr;
    }

    auto &&obj = std::get<RemoteObjectPtr>(value);
    return std::make_shared<ObjectTree::ObjectNode>(obj);
}
} // namespace quite::studio
