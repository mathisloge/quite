// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "rpc_set_object_property.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <quite/logger.hpp>
#include "error_helper.hpp"
#include "probe_value_converter.hpp"
#include "value.hpp"

DEFINE_LOGGER(rpc_set_object_properties)

namespace quite::proto
{
exec::task<void> SetObjectPropertyRpcHandler::operator()(SetObjectPropertyRPC &rpc,
                                                         const SetObjectPropertyRPC::Request &request)
{
    LOG_DEBUG(rpc_set_object_properties(), "START SetObjectProperty={}", request.object_id());

    const auto write_result =
        co_await probe_handler->set_property(request.object_id(),
                                             request.property(),
                                             convert_value(*value_registry, ProbeValueConverter{}, request.value()));
    if (not write_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(write_result.error()));
        co_return;
    }

    SetObjectPropertyRPC::Response response;
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<SetObjectPropertyRPC, SetObjectPropertyRpcHandler> make_rpc_set_object_property(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry)
{
    return agrpc::register_sender_rpc_handler<SetObjectPropertyRPC>(
        grpc_context, service, SetObjectPropertyRpcHandler{std::move(probe_handler), std::move(value_registry)});
}
} // namespace quite::proto
