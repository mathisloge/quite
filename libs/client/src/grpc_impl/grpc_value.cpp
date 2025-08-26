// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "grpc_value.hpp"
#include <entt/meta/pointer.hpp>
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
        RemoteObjectPtr obj = std::make_shared<GrpcRemoteObject>(std::move(ref), client);
        return entt::meta_any{std::move(obj)};
    }
    return {};
}
} // namespace quite::client
