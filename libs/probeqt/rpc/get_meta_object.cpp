#include "get_meta_object.hpp"
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/logger.hpp>
#include "../qtstdexec.h"

DEFINE_LOGGER(rpc_get_meta_object)

namespace quite::probe
{
exec::task<void> GetMetaObjectRpcHandler::operator()(GetMetaObjectRPC &rpc, const GetMetaObjectRPC::Request &request)
{
    LOG_TRACE_L1(rpc_get_meta_object, "START GetMetaObjectRpcHandler {}", request.type_name());

    GetMetaObjectRPC::Response response;

    co_return;
    //
    // FindObjectRPC::Response response{};
    // const auto obj_info = co_await stdexec::then(
    //    stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
    //    [&]() -> std::expected<ObjectInfo, ObjectErrC> { return tracker.find_object_by_query(request.query()); });
    //
    // if (obj_info.has_value())
    //{
    //    response.set_object_id(obj_info->object_id);
    //    co_await rpc.finish(response, grpc::Status::OK);
    //}
    // else
    //{
    //    co_await rpc.finish(response, grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find")});
    //}
}

agrpc::detail::RPCHandlerSender<GetMetaObjectRPC, GetMetaObjectRpcHandler> get_meta_object(
    agrpc::GrpcContext &grpc_context, quite::proto::MetaService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<GetMetaObjectRPC>(grpc_context, service, GetMetaObjectRpcHandler{});
}

} // namespace quite::probe
