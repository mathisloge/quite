#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "../object_tracker.hpp"

namespace quite::probe
{
using FindObjectRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;
struct FindObjectRpcHandler
{
    ObjectTracker &tracker;
    exec::task<void> operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> find_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker);
} // namespace quite::probe
