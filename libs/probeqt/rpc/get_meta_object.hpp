#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/meta_service.grpc.pb.h>
#include "meta_adapter.hpp"

namespace quite::probe
{
using GetMetaObjectRPC = agrpc::ServerRPC<&quite::proto::MetaService::AsyncService::RequestGetMetaObject>;
struct GetMetaObjectRpcHandler
{
    MetaAdapter &meta_adapter;
    exec::task<void> operator()(GetMetaObjectRPC &rpc, const GetMetaObjectRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<GetMetaObjectRPC, GetMetaObjectRpcHandler> get_meta_object(
    agrpc::GrpcContext &grpc_context, quite::proto::MetaService::AsyncService &service, MetaAdapter &meta_adapter);
} // namespace quite::probe
