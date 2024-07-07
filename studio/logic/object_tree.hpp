#pragma once
#include <exec/async_scope.hpp>
#include <quite/remote_object.hpp>

namespace quite::studio
{
class ObjectTree final
{
  public:
    explicit ObjectTree(RemoteObjectPtr root);
    ~ObjectTree();

    struct ObjectNode
    {
        RemoteObjectPtr object{nullptr};
        std::unordered_map<std::string, PropertyPtr> properties;
        std::shared_ptr<ObjectNode> parent{nullptr};
        std::vector<std::shared_ptr<ObjectNode>> leafs;
    };
    using ObjectNodePtr = std::shared_ptr<ObjectNode>;

    const ObjectNodePtr &root() const;

  private:
    void init_from_properties(const ObjectNodePtr &node);
    void construct_node_from_properties(const ObjectNodePtr &node);
    static ObjectNodePtr create_from_property(PropertyPtr property);
    static ObjectNodePtr create_from_value(const Value &value);

  private:
    ObjectNodePtr root_;
    exec::async_scope scope_;
};
} // namespace quite::studio
