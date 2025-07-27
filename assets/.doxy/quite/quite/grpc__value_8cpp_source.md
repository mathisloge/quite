

# File grpc\_value.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**grpc\_impl**](dir_61027e8bdb8101310df75c312f0d65c4.md) **>** [**grpc\_value.cpp**](grpc__value_8cpp.md)

[Go to the documentation of this file](grpc__value_8cpp.md)


```C++
#include "grpc_value.hpp"
#include "grpc_impl/grpc_remote_object.hpp"

namespace quite::client
{
void GrpcValueConverter::set_client(std::shared_ptr<proto::ProbeClient> client)
{
    client_ = std::move(client);
}

entt::meta_any GrpcValueConverter::from(ObjectReference ref) const
{
    if (auto client = client_.lock(); client != nullptr)
    {
        return entt::forward_as_meta(std::make_shared<GrpcRemoteObject>(std::move(ref), client));
    }
    return {};
}
} // namespace quite::client
```


