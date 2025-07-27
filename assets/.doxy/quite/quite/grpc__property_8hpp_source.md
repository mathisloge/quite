

# File grpc\_property.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**grpc\_impl**](dir_61027e8bdb8101310df75c312f0d65c4.md) **>** [**grpc\_property.hpp**](grpc__property_8hpp.md)

[Go to the documentation of this file](grpc__property_8hpp.md)


```C++
#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/meta/meta_type_id.hpp>
#include <quite/meta/meta_types.hpp>
#include "grpc_remote_object.hpp"
#include "quite/client/property.hpp"

namespace quite::client
{
class GrpcProperty final : public Property
{
  public:
    QUITE_DISABLE_COPY_MOVE(GrpcProperty);
    explicit GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name, entt::meta_any initial_value);
    ~GrpcProperty() override;
    const std::string &name() const override;
    meta::TypeId type_id() const override;
    const Result<entt::meta_any> &value() const override;
    AsyncResult<entt::meta_any> read() override;
    AsyncResult<void> write(entt::meta_any value) override;

  private:
    std::shared_ptr<GrpcRemoteObject> parent_;
    std::string name_;
    meta::TypeId type_id_;
    Result<entt::meta_any> last_value_;
};

} // namespace quite::client
```


