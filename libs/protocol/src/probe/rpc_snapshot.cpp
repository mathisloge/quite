#include "rpc_snapshot.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>

namespace quite::proto
{

exec::task<void> CreateScreenshotRpcHandler::operator()(RpcSnapshot &rpc, const RpcSnapshot::Request &request) const
{
    co_await rpc.finish(grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<RpcSnapshot, CreateScreenshotRpcHandler> make_rpc_snapshot(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<RpcSnapshot>(grpc_context, service, CreateScreenshotRpcHandler{});
}
} // namespace quite::proto
