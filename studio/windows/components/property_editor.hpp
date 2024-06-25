#pragma once
#include <exec/async_scope.hpp>
#include <quite/remote_object.hpp>
namespace quite::studio
{

class PropertyEditor final
{
  public:
    explicit PropertyEditor(std::shared_ptr<RemoteObject> root);
    ~PropertyEditor();
    void draw();

  private:
    void fetch_root_properties();
    void draw_object(RemoteObject& object);
    void draw_property(Property& property);

  private:
    std::shared_ptr<RemoteObject> root_;
    exec::async_scope scope_;

    std::unordered_map<std::string, std::shared_ptr<Property>> root_properties_;
};

} // namespace quite::studio
