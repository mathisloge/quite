#pragma once
#include <quite/basic_remote_object.hpp>
#include "object_client.hpp"
namespace quite
{
class RemoteObject : public BasicRemoteObject
{
  public:
    explicit RemoteObject(const std::shared_ptr<ObjectClient> &api_handle, ObjectId id, std::string_view type_name);
    ~RemoteObject() override;

    exec::task<value_handle> get_property(std::string_view property_name) override;

    exec::task<void> mouse_click() override;

  private:
    std::shared_ptr<ObjectClient> api_handle_;
    const ObjectId id_;
    const std::string type_name_;
};
} // namespace quite
