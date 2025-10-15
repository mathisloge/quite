// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "grpc_value.hpp"
#include <entt/meta/pointer.hpp>
#include "grpc_impl/grpc_remote_object.hpp"

namespace quite::client
{
GrpcValueConverter::GrpcValueConverter(std::shared_ptr<GrpcProbeContext> probe_context)
    : probe_context_{std::move(probe_context)}
{}

entt::meta_any GrpcValueConverter::from(ObjectReference ref) const
{
    if (auto probe_context = probe_context_.lock(); probe_context != nullptr)
    {
        RemoteObjectPtr obj = std::make_shared<GrpcRemoteObject>(std::move(ref), probe_context);
        return entt::meta_any{std::move(obj)};
    }
    return {};
}
} // namespace quite::client
