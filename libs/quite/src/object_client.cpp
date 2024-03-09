#include "object_client.hpp"
#include <spdlog/spdlog.h>
#include "quite/detail/awaitable_client.hpp"

namespace quite
{

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
