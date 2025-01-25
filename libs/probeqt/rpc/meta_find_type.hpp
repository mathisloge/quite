#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/meta_service.grpc.pb.h>
#include "meta_adapter.hpp"

namespace quite::probe
{
using FindTypeRPC = agrpc::ServerRPC<&quite::proto::MetaService::AsyncService::RequestFindType>;
struct GetMetaObjectRpcHandler
{
    MetaAdapter &meta_adapter;
    exec::task<void> operator()(FindTypeRPC &rpc, const FindTypeRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<FindTypeRPC, GetMetaObjectRpcHandler> meta_find_type(
    agrpc::GrpcContext &grpc_context, quite::proto::MetaService::AsyncService &service, MetaAdapter &meta_adapter);
} // namespace quite::probe
