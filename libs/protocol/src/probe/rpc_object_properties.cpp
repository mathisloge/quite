#include "rpc_object_properties.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include <quite/logger.hpp>
#include <quite/proto/value.hpp>
#include <quite/value/value_registry.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/object_handler.hpp"

DEFINE_LOGGER(rpc_get_object_properties)

namespace quite::proto
{

exec::task<void> GetObjectPropertiesRpcHandler::operator()(GetObjectPropertiesRPC &rpc,
                                                           const GetObjectPropertiesRPC::Request &request)
{
    LOG_DEBUG(rpc_get_object_properties(), "START RequestGetObjectProperty={}", request.object_id());
    auto &object_handler = entt::locator<IObjectHandler>::value();
    const auto properties_result = co_await object_handler.fetch_properties(request.object_id());
    if (not properties_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(properties_result.error()));
        co_return;
    }
    const auto &value_registry = entt::locator<ValueRegistry>::value();

    GetObjectPropertiesRPC::Response response;
    for (auto &&[key, value] : *properties_result)
    {
        response.mutable_property_values()->emplace(key, create_value(value_registry, value));
    }
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<GetObjectPropertiesRPC, GetObjectPropertiesRpcHandler> make_rpc_fetch_object_properties(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<GetObjectPropertiesRPC>(
        grpc_context, service, GetObjectPropertiesRpcHandler{});
}

} // namespace quite::proto
