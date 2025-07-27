

# File grpc\_remote\_object.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**grpc\_impl**](dir_61027e8bdb8101310df75c312f0d65c4.md) **>** [**grpc\_remote\_object.hpp**](grpc__remote__object_8hpp.md)

[Go to the documentation of this file](grpc__remote__object_8hpp.md)


```C++
#pragma once
#include <quite/client/remote_object.hpp>
#include <quite/value/object_id.hpp>
#include "quite/proto/client/probe_client.hpp"

namespace quite::client
{
class GrpcRemoteObject final : public std::enable_shared_from_this<GrpcRemoteObject>, public RemoteObject
{
  public:
    explicit GrpcRemoteObject(ObjectReference reference, std::shared_ptr<proto::ProbeClient> client);

    meta::TypeId type_id() const override;

    AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        std::vector<std::string> properties) override;

    AsyncResult<PropertyPtr> property(std::string property_name) override;
    AsyncResult<void> write_property(std::string property_name, entt::meta_any value) override;
    AsyncResult<entt::meta_any> fetch_property(std::string property_name);

    AsyncResult<void> mouse_action() override;

    AsyncResult<Image> take_snapshot() override;

    AsyncResult<void> invoke_method(std::string method_name) override;

  private:
    std::shared_ptr<proto::ProbeClient> client_;
    meta::TypeId type_id_;
};
} // namespace quite::client
```


