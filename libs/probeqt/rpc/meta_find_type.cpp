#include "meta_find_type.hpp"
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/logger.hpp>
#include <quite/proto/meta_converters.hpp>
#include "../qtstdexec.h"
#include "grpc_error.hpp"

DEFINE_LOGGER(rpc_get_meta_object)

namespace quite::probe
{
exec::task<void> GetMetaObjectRpcHandler::operator()(FindTypeRPC &rpc, const FindTypeRPC::Request &request)
{
    LOG_TRACE_L1(rpc_get_meta_object(), "START GetMetaObjectRpcHandler {}", request.type_id());

    FindTypeRPC::Response response;

    auto result = co_await meta_adapter.find_type_by_id(request.type_id());
    if (not result.has_value())
    {
        co_await rpc.finish_with_error(error2grpc_status(result.error()));
        co_return;
    }
    proto::to_protocol(*result, *response.mutable_type());
    co_await rpc.finish(response, grpc::Status::OK);

    co_return;
}

agrpc::detail::RPCHandlerSender<FindTypeRPC, GetMetaObjectRpcHandler> meta_find_type(
    agrpc::GrpcContext &grpc_context, quite::proto::MetaService::AsyncService &service, MetaAdapter &meta_adapter)
{
    return agrpc::register_sender_rpc_handler<FindTypeRPC>(
        grpc_context, service, GetMetaObjectRpcHandler{meta_adapter});
}

} // namespace quite::probe
