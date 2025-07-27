

# File rpc\_snapshot.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_snapshot.cpp**](rpc__snapshot_8cpp.md)

[Go to the documentation of this file](rpc__snapshot_8cpp.md)


```C++
#include "rpc_snapshot.hpp"
#include <ranges>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/probe_handler.hpp"

namespace quite::proto
{

exec::task<void> SnapshotRpcHandler::operator()(RpcSnapshot &rpc, const RpcSnapshot::Request &request) const
{
    auto result = co_await probe_handler->take_snapshot(request.object_id());
    if (not result.has_value())
    {
        co_await rpc.finish(result2grpc_status(result.error()));
        co_return;
    }
    constexpr std::int64_t k4Mb = 4'000'000;
    auto &image = *result;
    RpcSnapshot::Response response;
    response.mutable_metadata()->set_width(image.width);
    response.mutable_metadata()->set_height(image.height);
    const auto blocks = image.image_data | std::views::chunk(k4Mb);
    for (auto &&block : blocks)
    {
        response.mutable_data()->reserve(block.size());
        std::ranges::copy(block, std::back_inserter(*response.mutable_data()));

        const auto written = co_await rpc.write(response);
        if (not written)
        {
            co_await rpc.finish(grpc::Status::CANCELLED);
            co_return;
        }
        response.mutable_data()->clear();
    }
    co_await rpc.finish(grpc::Status::OK);
    co_return;
}

agrpc::detail::RPCHandlerSender<RpcSnapshot, SnapshotRpcHandler> make_rpc_snapshot(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler)
{
    return agrpc::register_sender_rpc_handler<RpcSnapshot>(
        grpc_context, service, SnapshotRpcHandler{std::move(probe_handler)});
}
} // namespace quite::proto
```


