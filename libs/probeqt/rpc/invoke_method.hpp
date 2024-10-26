#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "method_invoker.hpp"

namespace quite::probe
{
using InvokeMethodRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestInvokeMethod>;
struct InvokeMethodRpcHandler
{
    ObjectTracker &object_tracker;
    MethodInvoker &method_invoker;
    exec::task<void> operator()(InvokeMethodRPC &, const InvokeMethodRPC::Request &);
};

agrpc::detail::RPCHandlerSender<InvokeMethodRPC, InvokeMethodRpcHandler> invoke_method(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ObjectTracker &object_tracker,
    MethodInvoker &method_invoker);
} // namespace quite::probe
