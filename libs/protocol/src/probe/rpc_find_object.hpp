#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/value/value_registry.hpp>
#include "probe_handler_handle.hpp"

namespace quite::proto
{
using FindObjectRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;
struct FindObjectRpcHandler
{
    ProbeHandlerHandle probe_handler;
    ServiceHandle<ValueRegistry> value_registry;
    exec::task<void> operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> make_rpc_find_object(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry);
} // namespace quite::proto
