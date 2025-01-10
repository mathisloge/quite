#include "invoke_method.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/core.h>
#include "object_tracker.hpp"
#include "proto_converters.hpp"

namespace quite::probe
{

exec::task<void> InvokeMethodRpcHandler::operator()(InvokeMethodRPC &rpc, const InvokeMethodRPC::Request &request)
{
    if (not request.has_method_call())
    {
        co_await rpc.finish(
            {}, grpc::Status{grpc::StatusCode::FAILED_PRECONDITION, "Can't invoke a method without a passed mathod."});
        co_return;
    }

    const auto object_id = request.object_id();
    auto object = object_tracker.get_object_by_id(object_id);
    if (not object.has_value())
    {
        co_await rpc.finish({},
                            grpc::Status{grpc::StatusCode::FAILED_PRECONDITION, "Could not find object with given id"});
        co_return;
    }

    InvokeMethodRPC::Response response;

    std::vector<entt::meta_any> params;
    std::ranges::transform(request.method_call().argument(), std::back_inserter(params), meta_from_value);

    auto result =
        method_invoker.invoke_method(entt::meta_any{object.value()}, request.method_call().method_name(), params);

    if (not result.has_value())
    {
        co_await rpc.finish({},
                            grpc::Status{grpc::StatusCode::ABORTED,
                                         fmt::format("Could not invoke method due to: {}", result.error().message)});
        co_return;
    }
    if (result->allow_cast<proto::Value>())
    {
        *response.mutable_return_value()->mutable_value() = result->cast<proto::Value>();
        co_await rpc.finish(response,
                            grpc::Status{grpc::StatusCode::ABORTED,
                                         fmt::format("Could not invoke method due to: {}", result.error().message)});
        co_return;
    }
    co_await rpc.finish(
        {}, grpc::Status{grpc::StatusCode::ABORTED, fmt::format("Couild not convert return object to protocol value")});
}

agrpc::detail::RPCHandlerSender<InvokeMethodRPC, InvokeMethodRpcHandler> invoke_method(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ObjectTracker &object_tracker,
    MethodInvoker &method_invoker)
{
    return agrpc::register_sender_rpc_handler<InvokeMethodRPC>(
        grpc_context, service, InvokeMethodRpcHandler{object_tracker, method_invoker});
}
} // namespace quite::probe
