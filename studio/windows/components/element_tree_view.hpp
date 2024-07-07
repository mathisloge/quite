#pragma once
#include <quite/remote_object.hpp>
#include "object_tree.hpp"
#include "property_editor.hpp"
#include "image_view.hpp"
namespace quite::studio
{
class ElementTreeView
{
  public:
    explicit ElementTreeView(ObjectTree& tree, PropertyEditor& property_editor, ImageView& image_view);
    ~ElementTreeView();
    void draw();

  private:
    void draw_tree_node(const ObjectTree::ObjectNode &node);

  private:
    ObjectTree& tree_;
    const ObjectTree::ObjectNode *current_{nullptr};
    PropertyEditor& property_editor_;
    ImageView& image_view_;
};
} // namespace quite::studio
