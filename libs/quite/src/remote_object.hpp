#pragma once
#include <quite/basic_remote_object.hpp>
#include "api_handle.hpp"
#include "object_client.hpp"
namespace quite
{
class RemoteObject : public BasicRemoteObject
{
  public:
    explicit RemoteObject(const std::shared_ptr<ApiHandle> &api_handle, ObjectId id, std::string_view type_name);
    ~RemoteObject() override;

    ObjectId id() const noexcept override;
    std::shared_ptr<ApiHandle> api_handle() const override;

    exec::task<void> mouse_click() override;
    exec::task<void> take_snapshot() override;

  private:
    std::shared_ptr<ApiHandle> api_handle_;
    const ObjectId id_;
    const std::string type_name_;
};
} // namespace quite
