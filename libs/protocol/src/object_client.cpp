#include "quite/object_client.hpp"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include "awaitable_client.hpp"
#include <spdlog/spdlog.h>

namespace quite
{
ObjectClient::ObjectClient(agrpc::GrpcContext &context)
    : context_{context}
    , stub_{grpc::CreateChannel(std::string("localhost:50051"), grpc::InsecureChannelCredentials())}
{}

ObjectClient::~ObjectClient() = default;

asio::awaitable<std::string> ObjectClient::sayHello(const std::string &name)
{
    using RPC = awaitable_client_t<&proto::ObjectService::Stub::PrepareAsyncSayHello>;
    grpc::ClientContext client_context;
    proto::HelloRequest request;
    request.set_name("world");
    proto::HelloReply response;
    const auto status = co_await RPC::request(context_, stub_, client_context, request, response);

    spdlog::error("STATUS: {}", status.error_message());
    co_return response.message();
}
} // namespace quite
