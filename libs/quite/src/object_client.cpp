#include "object_client.hpp"
#include <spdlog/spdlog.h>
#include "detail/awaitable_client.hpp"
#include "remote_object.hpp"

namespace
{
void setupClientContext(grpc::ClientContext &client_context)
{
    client_context.set_wait_for_ready(true);
}
} // namespace
namespace quite
{

asio::awaitable<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> ObjectClient::findObject()
{
    using RPC = awaitable_client_t<&proto::ObjectService::Stub::PrepareAsyncFindObject>;

    grpc::ClientContext client_context;
    setupClientContext(client_context);
    proto::ObjectRequest request;
    *request.mutable_object_name() = "testRoot2";

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
        co_return std::make_shared<RemoteObject>();
    }

    co_return std::unexpected(FindObjectErrorCode::object_not_found);
}
} // namespace quite
