#pragma once
#include <quite/remote_object.hpp>

namespace quite::studio
{
class ElementTreeView
{
  public:
    explicit ElementTreeView(std::shared_ptr<RemoteObject> root);
    ~ElementTreeView();
    void draw();

  private:
    class TreeElement;
    void set_selected_element(std::shared_ptr<TreeElement> element);

  private:
    std::shared_ptr<TreeElement> root_;
    std::shared_ptr<TreeElement> current_;
};
} // namespace quite::studio
