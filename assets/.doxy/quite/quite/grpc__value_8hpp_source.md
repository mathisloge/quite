

# File grpc\_value.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**grpc\_impl**](dir_61027e8bdb8101310df75c312f0d65c4.md) **>** [**grpc\_value.hpp**](grpc__value_8hpp.md)

[Go to the documentation of this file](grpc__value_8hpp.md)


```C++
#pragma once
#include <quite/proto/client/probe_client.hpp>
#include <quite/proto/client/value_converter.hpp>
namespace quite::client
{
class GrpcValueConverter final : public proto::IValueConverter
{
  public:
    void set_client(std::shared_ptr<proto::ProbeClient> client);
    entt::meta_any from(ObjectReference ref) const override;

  private:
    std::weak_ptr<proto::ProbeClient> client_;
};
// quite::Result<quite::Value> convert(const entt::meta_any &value, std::shared_ptr<proto::ProbeClient> client);
} // namespace quite::client
```


