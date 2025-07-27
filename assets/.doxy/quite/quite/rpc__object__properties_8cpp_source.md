

# File rpc\_object\_properties.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_object\_properties.cpp**](rpc__object__properties_8cpp.md)

[Go to the documentation of this file](rpc__object__properties_8cpp.md)


```C++
#include "rpc_object_properties.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include <quite/logger.hpp>
#include <quite/value/value_registry.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/probe_handler.hpp"
#include "value.hpp"

DEFINE_LOGGER(rpc_get_object_properties)

namespace quite::proto
{

exec::task<void> GetObjectPropertiesRpcHandler::operator()(GetObjectPropertiesRPC &rpc,
                                                           const GetObjectPropertiesRPC::Request &request)
{
    LOG_DEBUG(rpc_get_object_properties(), "START RequestGetObjectProperty={}", request.object_id());
    std::vector<std::string> property_names;
    property_names.reserve(request.property_names_size());
    std::move(request.property_names().begin(), request.property_names().end(), std::back_inserter(property_names));
    const auto properties_result =
        co_await probe_handler->fetch_properties(request.object_id(), std::move(property_names));
    if (not properties_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(properties_result.error()));
        co_return;
    }

    GetObjectPropertiesRPC::Response response;
    for (auto &&[key, value] : *properties_result)
    {
        response.mutable_property_values()->insert({key, create_value(*value_registry, value)});
    }
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<GetObjectPropertiesRPC, GetObjectPropertiesRpcHandler> make_rpc_fetch_object_properties(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry)
{
    return agrpc::register_sender_rpc_handler<GetObjectPropertiesRPC>(
        grpc_context, service, GetObjectPropertiesRpcHandler{std::move(probe_handler), std::move(value_registry)});
}

} // namespace quite::proto
```


