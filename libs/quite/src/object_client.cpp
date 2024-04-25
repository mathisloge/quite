#include "object_client.hpp"
#include <spdlog/spdlog.h>
#include "quite/detail/awaitable_client.hpp"

namespace {
    void setupClientContext(grpc::ClientContext& client_context) {
        client_context.set_wait_for_ready(true);
    }
}
namespace quite
{

asio::awaitable<std::string> ObjectClient::sayHello(const std::string &name)
{
    using RPC = awaitable_client_t<&proto::ObjectService::Stub::PrepareAsyncSayHello>;
    grpc::ClientContext client_context;
    setupClientContext(client_context);
    proto::HelloRequest request;
    request.set_name("world");
    proto::HelloReply response;
    const auto status = co_await RPC::request(context_, stub_, client_context, request, response);

    spdlog::error("STATUS: {}", status.error_message());
    co_return response.message();
}

asio::awaitable<void> ObjectClient::findObject()
{
    using RPC = awaitable_client_t<&proto::ObjectService::Stub::PrepareAsyncFindObject>;

    grpc::ClientContext client_context;
    setupClientContext(client_context);
    proto::ObjectRequest request;
    *request.mutable_object_name() = "testRoot2";

    proto::ObjectReply response;

    spdlog::debug("start request");
    const auto status = co_await RPC::request(context_, stub_, client_context, request, response);

    spdlog::error("findObject reply: err:{}, code: {}", status.error_message(), static_cast<int>(status.error_code()));
}
} // namespace quite
