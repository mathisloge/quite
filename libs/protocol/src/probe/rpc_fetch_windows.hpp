#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::proto
{
using GetViewsRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetViews>;
struct GetViewsRpcHandler
{
    exec::task<void> operator()(GetViewsRPC &rpc, const GetViewsRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<GetViewsRPC, GetViewsRpcHandler> make_rpc_fetch_windows(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::proto
