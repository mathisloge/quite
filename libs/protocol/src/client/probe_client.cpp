#include "quite/proto/client/probe_client.hpp"
#include <agrpc/grpc_context.hpp>
#include <entt/locator/locator.hpp>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include "grpc_manager.hpp"
#include "probe_service_impl.hpp"
#include "quite/proto/meta_service.grpc.pb.h"
#include "quite/proto/probe.grpc.pb.h"

namespace quite::proto
{
struct ProbeClient::Impl
{
    Impl(std::string connection_url)
        : grpc_channel_{::grpc::CreateChannel(std::move(connection_url), ::grpc::InsecureChannelCredentials())}
    {}

    std::shared_ptr<agrpc::GrpcContext> grpc_context_{entt::locator<GrpcManager>::value_or().context()};
    std::shared_ptr<grpc::Channel> grpc_channel_;
    proto::ProbeService::Stub probe_service_stub_{grpc_channel_};
    proto::MetaService::Stub meta_service_stub_{grpc_channel_};
    ProbeServiceImpl probe_service_{grpc_context_, probe_service_stub_};
};

ProbeClient::ProbeClient(std::string connection_url)
    : impl_{std::make_unique<ProbeClient::Impl>(std::move(connection_url))}
{}

ProbeClient::~ProbeClient() = default;

IProbeService &ProbeClient::probe_service()
{
    return impl_->probe_service_;
}

core::IMouseInjector &ProbeClient::mouse_injector()
{}

meta::MetaRegistry &ProbeClient::meta_registry()
{}

} // namespace quite::proto
