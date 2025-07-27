#include "rpc_mouse_injection.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include <fmt/format.h>
#include <quite/injectors/mouse_injector.hpp>
#include <quite/logger.hpp>
#include "error_helper.hpp"

DEFINE_LOGGER(rpc_mouse_action_logger)
namespace
{
quite::core::MouseAction mouse_action_from_request(const quite::proto::MouseActionRPC::Request &request)
{
    return quite::core::MouseAction{
        .position = {request.relative_point().x(), request.relative_point().y()},
        .button =
            [btn = request.mouse_button()]() {
                switch (btn)
                {
                case quite::proto::left_button:
                    return quite::core::MouseButton::left;
                case quite::proto::right_button:
                    return quite::core::MouseButton::right;
                case quite::proto::middle_button:
                    return quite::core::MouseButton::middle;
                case quite::proto::MouseButton_INT_MIN_SENTINEL_DO_NOT_USE_:
                case quite::proto::MouseButton_INT_MAX_SENTINEL_DO_NOT_USE_:
                    break;
                }
                return quite::core::MouseButton::none;
            }(),
        .trigger =
            [trigger = request.mouse_action()]() {
                switch (trigger)
                {
                case quite::proto::none:
                    return quite::core::MouseTrigger::none;
                case quite::proto::click:
                    return quite::core::MouseTrigger::click;
                case quite::proto::double_click:
                    return quite::core::MouseTrigger::double_click;
                case quite::proto::press:
                    return quite::core::MouseTrigger::press;
                case quite::proto::release:
                    return quite::core::MouseTrigger::release;
                case quite::proto::move:
                    return quite::core::MouseTrigger::move;
                case quite::proto::MouseAction_INT_MIN_SENTINEL_DO_NOT_USE_:
                case quite::proto::MouseAction_INT_MAX_SENTINEL_DO_NOT_USE_:
                    break;
                }
                return quite::core::MouseTrigger::none;
            }(),
        .modifier =
            [modifier = request.modifier_key()]() {
                switch (modifier)
                {
                case quite::proto::no_key:
                    return quite::core::KeyboardModifier::none;
                case quite::proto::shift:
                    return quite::core::KeyboardModifier::shift;
                case quite::proto::crtl:
                    return quite::core::KeyboardModifier::control;
                case quite::proto::alt:
                    return quite::core::KeyboardModifier::alt;
                case quite::proto::meta:
                    return quite::core::KeyboardModifier::meta;
                default:
                    break;
                }
                return quite::core::KeyboardModifier::none;
            }(),
    };
}
} // namespace
namespace quite::proto
{
exec::task<void> MouseActionRpcHandler::operator()(MouseActionRPC &rpc, const MouseActionRPC::Request &request) const
{
    LOG_TRACE_L1(rpc_mouse_action_logger(), "START RequestMouseAction={}", request.object_id());

    const auto action = mouse_action_from_request(request);

    const auto invoke_result = co_await mouse_injector->single_action(request.object_id(), action);
    if (not invoke_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(invoke_result.error()));
        co_return;
    }
    MouseActionRPC::Response response{};
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<MouseActionRPC, MouseActionRpcHandler> make_rpc_mouse_injection(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ServiceHandle<core::IMouseInjector> mouse_injector)
{
    return agrpc::register_sender_rpc_handler<MouseActionRPC>(
        grpc_context, service, MouseActionRpcHandler{std::move(mouse_injector)});
}

} // namespace quite::proto
