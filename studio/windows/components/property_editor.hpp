#pragma once
#include <exec/async_scope.hpp>
#include <quite/remote_object.hpp>
namespace quite::studio
{

class PropertyEditor final
{
  public:
    class PropertyUi;

    explicit PropertyEditor(std::shared_ptr<RemoteObject> root);
    ~PropertyEditor();
    void draw();

  private:
    std::unique_ptr<PropertyUi> root_;
};
} // namespace quite::studio
