#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::proto
{
using InvokeMethodRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestInvokeMethod>;
struct InvokeMethodRpcHandler
{
    exec::task<void> operator()(InvokeMethodRPC &, const InvokeMethodRPC::Request &);
};

agrpc::detail::RPCHandlerSender<InvokeMethodRPC, InvokeMethodRpcHandler> make_rpc_invoke_method(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::proto
