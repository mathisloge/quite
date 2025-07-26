#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "probe/probe_handler_handle.hpp"
#include "quite/value/value_registry.hpp"

namespace quite::proto
{
using SetObjectPropertyRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestSetObjectProperty>;
struct SetObjectPropertyRpcHandler
{
    ProbeHandlerHandle probe_handler;
    ServiceHandle<ValueRegistry> value_registry;
    exec::task<void> operator()(SetObjectPropertyRPC &rpc, const SetObjectPropertyRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<SetObjectPropertyRPC, SetObjectPropertyRpcHandler> make_rpc_set_object_property(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry);
} // namespace quite::proto
