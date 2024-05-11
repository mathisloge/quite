#include "object_client.hpp"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>

namespace quite
{

ObjectClient::ObjectClient(agrpc::GrpcContext &grpc_context)
    : grpc_context_{grpc_context}
    , stub_{grpc::CreateChannel(std::string("localhost:50051"), grpc::InsecureChannelCredentials())}
{}
} // namespace quite
