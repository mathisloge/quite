#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "../injector/mouse_injector.hpp"
namespace quite::probe
{
using MouseActionRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMouseAction>;
struct MouseActionRpcHandler
{
    MouseInjector &mouse_injector;
    exec::task<void> operator()(MouseActionRPC &, const MouseActionRPC::Request &);
};

agrpc::detail::RPCHandlerSender<MouseActionRPC, MouseActionRpcHandler> mouse_action(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, MouseInjector &mouse_injector);
} // namespace quite::probe
