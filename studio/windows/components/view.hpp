#pragma once
#include <imgui.h>
#include <quite/application.hpp>
#include "element_tree_view.hpp"
#include "image_view.hpp"
#include "property_editor.hpp"
namespace quite::studio
{
class View final
{
  public:
    explicit View(const std::shared_ptr<RemoteObject> &view);
    ~View();

    void draw();

  private:
    std::shared_ptr<RemoteObject> view_;

    ObjectTree tree_;
    PropertyEditor prop_editor_;
    ElementTreeView element_view_;
    ImageView image_view_;
};
} // namespace quite::studio
