#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
namespace quite::proto
{
using MouseActionRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMouseAction>;
struct MouseActionRpcHandler
{
    exec::task<void> operator()(MouseActionRPC &, const MouseActionRPC::Request &);
};

agrpc::detail::RPCHandlerSender<MouseActionRPC, MouseActionRpcHandler> make_rpc_mouse_injection(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::proto
