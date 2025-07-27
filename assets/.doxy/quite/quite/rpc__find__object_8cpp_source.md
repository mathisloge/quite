

# File rpc\_find\_object.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_find\_object.cpp**](rpc__find__object_8cpp.md)

[Go to the documentation of this file](rpc__find__object_8cpp.md)


```C++
#include "rpc_find_object.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/value/object_query.hpp>
#include <quite/value/value_registry.hpp>
#include "error_helper.hpp"
#include "probe_value_converter.hpp"
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
        properties.emplace(prop.first, convert_value(value_registry, ProbeValueConverter{}, prop.second));
    }
    return properties;
}
} // namespace

exec::task<void> FindObjectRpcHandler::operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request)
{
    ObjectQuery object_query;
    object_query.properties = convert_properties(*value_registry, request.query().properties());
    object_query.type_name = request.query().has_type_name() ? request.query().type_name() : "";
    ObjectQuery *child = &object_query;
    const proto::ObjectSearchQuery *parent{&request.query()};
    while (parent->has_parent())
    {
        parent = &request.query().parent();
        child->container = std::make_shared<ObjectQuery>();
        child->container->properties = convert_properties(*value_registry, parent->properties());
        child = child->container.get();
    }

    auto find_result = co_await probe_handler->find_object(std::move(object_query));
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
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry)
{
    return agrpc::register_sender_rpc_handler<FindObjectRPC>(
        grpc_context, service, FindObjectRpcHandler{std::move(probe_handler), std::move(value_registry)});
}

} // namespace quite::proto
```


