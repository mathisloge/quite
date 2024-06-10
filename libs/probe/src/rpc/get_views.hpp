#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "../object_tracker.hpp"

namespace quite::probe
{
using GetViewsRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetViews>;
struct GetViewsRpcHandler
{
    ObjectTracker &tracker;
    exec::task<void> operator()(GetViewsRPC &rpc, const GetViewsRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<GetViewsRPC, GetViewsRpcHandler> get_views(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker);
} // namespace quite::probe
