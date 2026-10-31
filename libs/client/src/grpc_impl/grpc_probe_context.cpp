// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "grpc_probe_context.hpp"
namespace quite::client
{
void GrpcProbeContext::set_client(std::shared_ptr<proto::ProbeClient> client)
{
    client_ = std::move(client);
}

proto::ProbeClient &GrpcProbeContext::client()
{
    if (client_ == nullptr)
    {
        throw std::runtime_error("Client was not set before.");
    }
    return *client_;
}

core::IMouseInjector &GrpcProbeContext::mouse_injector()
{
    return client_->mouse_injector();
}
} // namespace quite::client
