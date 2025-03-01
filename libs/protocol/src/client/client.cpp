#include "quite/proto/client/client.hpp"
#include "grpc_manager.hpp"
#include "probe_client_impl.hpp"

namespace quite::proto
{
struct Client::Impl
{
    GrpcManager grpc_;
};

Client::Client(entt::locator<ValueRegistry>::node_type value_registry,
               entt::locator<asio2exec::asio_context>::node_type io_context)
    : impl_{std::make_unique<Impl>()}
{
    entt::locator<ValueRegistry>::reset(std::move(value_registry));
    entt::locator<asio2exec::asio_context>::reset(std::move(io_context));
}

Client::~Client() = default;

std::shared_ptr<ProbeClient> Client::create_probe_client(std::string connection_url)
{
    return std::make_shared<ProbeClientImpl>(impl_->grpc_, std::move(connection_url));
}

} // namespace quite::proto
