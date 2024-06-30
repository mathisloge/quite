#include "get_views.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>

namespace
{}

namespace quite::probe
{
exec::task<void> GetViewsRpcHandler::operator()(GetViewsRPC &rpc, const GetViewsRPC::Request &request)
{
    GetViewsRPC::Response response;

    for (auto obj : tracker.top_level_views())
    {
        response.mutable_object_id()->Add(reinterpret_cast<ObjectId>(obj));
    }

    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<GetViewsRPC, GetViewsRpcHandler> get_views(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker)
{
    return agrpc::register_sender_rpc_handler<GetViewsRPC>(grpc_context, service, GetViewsRpcHandler{tracker});
}

} // namespace quite::probe
