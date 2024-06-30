#include "metatype_from_object.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/task.hpp>
#include <fmt/format.h>

namespace quite::probe
{

exec::task<void> MetaTypeFromObjectRpcHandler::operator()(MetaTypeFromObjectRPC &rpc,
                                                          const MetaTypeFromObjectRPC::Request &request)
{
    MetaTypeFromObjectRPC::Response response;

    co_await rpc.finish(response, grpc::Status{grpc::StatusCode::UNIMPLEMENTED, "Method not implemented yet."});
}

agrpc::detail::RPCHandlerSender<MetaTypeFromObjectRPC, MetaTypeFromObjectRpcHandler> metatype_from_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<MetaTypeFromObjectRPC>(
        grpc_context, service, MetaTypeFromObjectRpcHandler{});
}

} // namespace quite::probe
