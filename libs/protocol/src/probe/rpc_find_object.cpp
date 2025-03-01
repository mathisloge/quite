#include "rpc_find_object.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/value/object_query.hpp>
#include <quite/value/value_registry.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/probe_handler.hpp"
#include "value.hpp"

namespace quite::proto
{
namespace
{
ObjectQuery::PropertyMap convert_properties(const ValueRegistry &value_registry,
                                            const ::google::protobuf::Map<std::string, Value> &proto_properties)
{
    ObjectQuery::PropertyMap properties;
    for (auto &&prop : proto_properties)
    {
        properties.emplace(prop.first, convert_value(value_registry, prop.second));
    }
    return properties;
}
} // namespace

exec::task<void> FindObjectRpcHandler::operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request)
{
    const auto &value_registry = entt::locator<ValueRegistry>::value();
    ObjectQuery object_query;
    object_query.properties = convert_properties(value_registry, request.query().properties());
    ObjectQuery *child = &object_query;
    const proto::ObjectSearchQuery *parent{&request.query()};
    while (parent->has_parent())
    {
        parent = &request.query().parent();
        child->container = std::make_shared<ObjectQuery>();
        child->container->properties = convert_properties(value_registry, parent->properties());
        child = child->container.get();
    }

    auto &snapshot_handler = entt::locator<IProbeHandler>::value();
    auto find_result = co_await snapshot_handler.find_object(std::move(object_query));
    if (not find_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(find_result.error()));
        co_return;
    }

    FindObjectRPC::Response response{};
    response.set_object_id(find_result->object_id);
    response.set_type_id(find_result->type_id);

    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> make_rpc_find_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<FindObjectRPC>(grpc_context, service, FindObjectRpcHandler{});
}

} // namespace quite::proto
