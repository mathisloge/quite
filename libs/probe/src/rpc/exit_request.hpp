#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::probe
{
using ExitRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestExit>;
struct ExitRpcHandler
{
    exec::task<void> operator()(ExitRPC &rpc, const ExitRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<ExitRPC, ExitRpcHandler> exit_request(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::probe
