#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/meta/meta_registry.hpp>
#include <quite/proto/meta_service.grpc.pb.h>
#include <quite/service_handle.hpp>

namespace quite::proto
{
using FindTypeRPC = agrpc::ServerRPC<&quite::proto::MetaService::AsyncService::RequestFindType>;
struct GetMetaObjectRpcHandler
{
    ServiceHandle<meta::MetaRegistry> meta_registry;
    exec::task<void> operator()(FindTypeRPC &rpc, const FindTypeRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<FindTypeRPC, GetMetaObjectRpcHandler> make_rpc_meta_find_type(
    agrpc::GrpcContext &grpc_context,
    quite::proto::MetaService::AsyncService &service,
    ServiceHandle<meta::MetaRegistry> meta_registry);
} // namespace quite::proto
