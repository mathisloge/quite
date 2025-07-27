// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "rpc_meta_find_type.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include <fmt/format.h>
#include <quite/logger.hpp>
#include <quite/meta/meta_registry.hpp>
#include "error_helper.hpp"
#include "meta_converters.hpp"

DEFINE_LOGGER(rpc_get_meta_object)

namespace quite::proto
{
exec::task<void> GetMetaObjectRpcHandler::operator()(FindTypeRPC &rpc, const FindTypeRPC::Request &request)
{
    LOG_TRACE_L1(rpc_get_meta_object(), "START GetMetaObjectRpcHandler {}", request.type_id());
    FindTypeRPC::Response response;

    auto result = co_await meta_registry->lookup_type(request.type_id());
    if (not result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(result.error()));
        co_return;
    }
    to_protocol(*result, *response.mutable_type());
    co_await rpc.finish(response, grpc::Status::OK);
    co_return;
}

agrpc::detail::RPCHandlerSender<FindTypeRPC, GetMetaObjectRpcHandler> make_rpc_meta_find_type(
    agrpc::GrpcContext &grpc_context,
    quite::proto::MetaService::AsyncService &service,
    ServiceHandle<meta::MetaRegistry> meta_registry)
{
    return agrpc::register_sender_rpc_handler<FindTypeRPC>(
        grpc_context, service, GetMetaObjectRpcHandler{std::move(meta_registry)});
}

} // namespace quite::proto
