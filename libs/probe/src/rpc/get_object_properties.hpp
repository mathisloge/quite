#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "../object_tracker.hpp"

namespace quite::probe
{
using GetObjectPropertiesRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetObjectProperties>;
struct GetObjectPropertiesRpcHandler
{
    ObjectTracker &tracker;
    exec::task<void> operator()(GetObjectPropertiesRPC &rpc, const GetObjectPropertiesRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<GetObjectPropertiesRPC, GetObjectPropertiesRpcHandler> get_object_properties(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker);
} // namespace quite::probe
