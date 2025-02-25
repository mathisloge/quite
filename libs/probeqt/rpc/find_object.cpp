#include "find_object.hpp"
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/logger.hpp>
#include "../qtstdexec.h"

DEFINE_LOGGER(rpc_find_object_logger)

namespace quite::probe
{
exec::task<void> FindObjectRpcHandler::operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request)
{
    LOG_DEBUG(rpc_find_object_logger(), "START RpcFindObject...");

    FindObjectRPC::Response response{};
    const auto obj_info = co_await stdexec::then(
        stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
        [&]() -> std::expected<ObjectInfo, ObjectErrC> { return tracker.find_object_by_query(request.query()); });

    if (obj_info.has_value())
    {
        response.set_object_id(obj_info->object_id);
        response.set_type_id(obj_info->class_type);
        LOG_DEBUG(rpc_find_object_logger(), "got object {}, {}", obj_info->object_id, obj_info->class_type);
        co_await rpc.finish(response, grpc::Status::OK);
    }
    else
    {
        LOG_DEBUG(rpc_find_object_logger(), "got not obj info");
        co_await rpc.finish(response, grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find")});
    }
}

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> find_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker)
{
    return agrpc::register_sender_rpc_handler<FindObjectRPC>(grpc_context, service, FindObjectRpcHandler{tracker});
}

} // namespace quite::probe
