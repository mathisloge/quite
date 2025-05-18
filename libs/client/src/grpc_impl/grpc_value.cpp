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
    return entt::forward_as_meta(std::make_shared<GrpcRemoteObject>(std::move(ref), client_));
}
} // namespace quite::client
