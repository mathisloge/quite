#include "object_client.hpp"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <spdlog/spdlog.h>
#include "detail/awaitable_client.hpp"
#include "remote_object.hpp"
#include "rpc/find_object_client_rpc.hpp"

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
        .and_then([](auto &&reply) -> std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode> {
            return std::make_shared<RemoteObject>(reply.id());
        })
        .or_else([](auto &&error) -> std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
    /*
        using RPC = awaitable_client_t<&proto::ObjectService::Stub::PrepareAsyncFindObject>;

        grpc::ClientContext client_context;
        setupClientContext(client_context);
        proto::ObjectRequest request;
        *request.mutable_object_name() = object_name;

        proto::ObjectReply response;

        spdlog::debug("start request");
        const auto status = co_await RPC::request(context_, stub_, client_context, request, response);
        spdlog::error("findObject reply: err:{}, code: {} type={}, id={}",
                      status.error_message(),
                      static_cast<int>(status.error_code()),
                      response.type_name(),
                      response.id());
        if (status.ok())
        {
            co_return std::make_shared<RemoteObject>(response.id());
        }

        co_return std::unexpected(FindObjectErrorCode::object_not_found);
        */
}
} // namespace quite
