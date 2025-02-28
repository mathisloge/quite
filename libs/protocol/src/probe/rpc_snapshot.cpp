#include "rpc_snapshot.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/probe_handler.hpp"

namespace quite::proto
{

exec::task<void> SnapshotRpcHandler::operator()(RpcSnapshot &rpc, const RpcSnapshot::Request &request) const
{
    auto &object_handler = entt::locator<IProbeHandler>::value();
    auto result = co_await object_handler.take_snapshot(request.object_id());
    if (not result.has_value())
    {
        co_await rpc.finish(result2grpc_status(result.error()));
        co_return;
    }
    constexpr std::int64_t k4Mb = 4000000;
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
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<RpcSnapshot>(grpc_context, service, SnapshotRpcHandler{});
}
} // namespace quite::proto
