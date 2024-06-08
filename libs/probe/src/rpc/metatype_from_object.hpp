#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::probe
{
using MetaTypeFromObjectRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMetaTypeFromObject>;
struct MetaTypeFromObjectRpcHandler
{
    exec::task<void> operator()(MetaTypeFromObjectRPC &, const MetaTypeFromObjectRPC::Request &);
};

agrpc::detail::RPCHandlerSender<MetaTypeFromObjectRPC, MetaTypeFromObjectRpcHandler> metatype_from_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service);
} // namespace quite::probe
