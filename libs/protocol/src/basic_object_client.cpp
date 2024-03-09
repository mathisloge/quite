#include "quite/basic_object_client.hpp"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>

namespace quite
{
BasicObjectClient::BasicObjectClient(agrpc::GrpcContext &context)
    : context_{context}
    , stub_{grpc::CreateChannel(std::string("localhost:50051"), grpc::InsecureChannelCredentials())}
{}

BasicObjectClient::~BasicObjectClient() = default;
} // namespace quite
