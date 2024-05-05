#include "object_client.hpp"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>
#include "remote_object.hpp"
#include "rpc/make_find_object_request.hpp"

namespace
{
void setupClientContext(grpc::ClientContext &client_context)
{
    client_context.set_wait_for_ready(true);
}
} // namespace
namespace quite
{

ObjectClient::ObjectClient(agrpc::GrpcContext &grpc_context)
    : grpc_context_{grpc_context}
    , stub_{grpc::CreateChannel(std::string("localhost:50051"), grpc::InsecureChannelCredentials())}
{}

exec::task<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> ObjectClient::find_object(
    std::string_view object_name)
{
    spdlog::error("START RESPONSE!");
    const auto response = co_await make_find_object_request(grpc_context_, stub_, object_name);
    spdlog::error("GOT RESPONSE!");
    co_return response
        .and_then([this](auto &&reply) -> std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode> {
            return std::make_shared<RemoteObject>(shared_from_this(), reply.id(), reply.type_name());
        })
        .or_else([](auto &&error) -> std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
}
} // namespace quite
