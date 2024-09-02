#include "probe_client.hpp"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

namespace quite::grpc_impl
{

ProbeClient::ProbeClient(std::shared_ptr<agrpc::GrpcContext> grpc_context)
    : grpc_context_{std::move(grpc_context)}
    , grpc_channel_{::grpc::CreateChannel(std::string("unix:///tmp/grpc_probe.sock"),
                                          ::grpc::InsecureChannelCredentials())}
    , stub_{grpc_channel_}
    , meta_service_stub_{grpc_channel_}
{}
} // namespace quite::grpc_impl
