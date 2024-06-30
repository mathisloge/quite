#include "find_object.hpp"
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "../qtstdexec.h"

namespace quite::probe
{
exec::task<void> FindObjectRpcHandler::operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request)
{
    spdlog::debug("START RpcFindObject");

    FindObjectRPC::Response response{};
    auto obj_info =
        co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                               [&]() -> std::expected<ObjectInfo, ObjectErrC> {
                                   auto it = request.query().properties().find("objectName");
                                   if (it != request.query().properties().end())
                                   {
                                       return tracker.findObject(it->second);
                                   }
                                   return std::unexpected(ObjectErrC::not_found);
                               });

    if (obj_info.has_value())
    {
        response.set_object_id(obj_info->object_id);
        co_await rpc.finish(response, grpc::Status::OK);
    }
    else
    {
        co_await rpc.finish(response, grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find")});
    }
}

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> find_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker)
{
    return agrpc::register_sender_rpc_handler<FindObjectRPC>(grpc_context, service, FindObjectRpcHandler{tracker});
}

} // namespace quite::probe
