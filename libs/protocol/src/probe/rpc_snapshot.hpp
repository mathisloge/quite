#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::proto
{
using RpcSnapshot = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestCreateScreenshot>;
struct CreateScreenshotRpcHandler
{
    exec::task<void> operator()(RpcSnapshot &rpc, const RpcSnapshot::Request &request) const;
};

agrpc::detail::RPCHandlerSender<RpcSnapshot, CreateScreenshotRpcHandler> make_rpc_snapshot(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::proto
