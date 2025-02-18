#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::proto
{
using FindObjectRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;
struct FindObjectRpcHandler
{
    exec::task<void> operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> find_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::proto
