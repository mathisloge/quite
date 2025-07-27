

# File rpc\_invoke\_method.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_invoke\_method.cpp**](rpc__invoke__method_8cpp.md)

[Go to the documentation of this file](rpc__invoke__method_8cpp.md)


```C++
#include "rpc_invoke_method.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include <fmt/core.h>
#include "error_helper.hpp"
#include "probe_value_converter.hpp"
#include "quite/proto/probe/probe_handler.hpp"
#include "value.hpp"

namespace quite::proto
{

exec::task<void> InvokeMethodRpcHandler::operator()(InvokeMethodRPC &rpc, const InvokeMethodRPC::Request &request) const
{
    if (not request.has_method_call())
    {
        co_await rpc.finish_with_error(
            grpc::Status{grpc::StatusCode::FAILED_PRECONDITION, "Can't invoke a method without a passed method."});
        co_return;
    }
    auto root_object = co_await probe_handler->object_instance(request.object_id());
    if (not root_object.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(root_object.error()));
        co_return;
    }

    std::vector<entt::meta_any> params;
    std::ranges::transform(request.method_call().argument(), std::back_inserter(params), [this](auto &&arg) {
        return convert_value(*value_registry, ProbeValueConverter{}, arg);
    });
    auto invoke_result =
        co_await probe_handler->invoke_method(*root_object, request.method_call().method_name(), std::move(params));
    if (not invoke_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(invoke_result.error()));
        co_return;
    }
    InvokeMethodRPC::Response response;
    if (invoke_result->type().info() == entt::type_id<void>())
    {
        co_await rpc.finish(response, grpc::Status::OK);
        co_return;
    }
    *response.mutable_return_value()->mutable_value() = create_value(*value_registry, *invoke_result);
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<InvokeMethodRPC, InvokeMethodRpcHandler> make_rpc_invoke_method(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry)
{
    return agrpc::register_sender_rpc_handler<InvokeMethodRPC>(
        grpc_context, service, InvokeMethodRpcHandler{std::move(probe_handler), std::move(value_registry)});
}
} // namespace quite::proto
```


