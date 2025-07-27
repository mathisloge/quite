// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/proto/client/client.hpp"
#include "grpc_manager.hpp"
#include "probe_client_impl.hpp"
#include "quite/proto/client/value_converter.hpp"

namespace quite::proto
{
struct Client::Impl
{
    GrpcManager grpc_;
};

Client::Client(entt::locator<ValueRegistry>::node_type value_registry)
    : impl_{std::make_unique<Impl>()}
{
    entt::locator<ValueRegistry>::reset(std::move(value_registry));
}

Client::~Client() = default;

std::shared_ptr<ProbeClient> Client::create_probe_client(std::shared_ptr<IValueConverter> value_converter,
                                                         std::string connection_url)
{
    return std::make_shared<ProbeClientImpl>(impl_->grpc_, std::move(connection_url), std::move(value_converter));
}

} // namespace quite::proto
