// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "rpc_fetch_windows.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/probe_handler.hpp"

namespace quite::proto
{
exec::task<void> GetViewsRpcHandler::operator()(GetViewsRPC &rpc, const GetViewsRPC::Request &request) const
{
    auto windows_result = co_await probe_handler->fetch_windows();
    if (not windows_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(windows_result.error()));
        co_return;
    }

    GetViewsRPC::Response response;
    for (auto &&obj : windows_result.value())
    {
        auto &&proto_obj = response.add_object();
        proto_obj->set_type_id(obj.type_id);
        proto_obj->set_object_id(obj.type_id);
    }
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<GetViewsRPC, GetViewsRpcHandler> make_rpc_fetch_windows(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler)
{
    return agrpc::register_sender_rpc_handler<GetViewsRPC>(
        grpc_context, service, GetViewsRpcHandler{std::move(probe_handler)});
}

} // namespace quite::proto
