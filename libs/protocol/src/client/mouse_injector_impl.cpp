#include "mouse_injector_impl.hpp"
#include "configure_client_context.hpp"
#include "error_helper.hpp"

namespace quite::proto
{
MouseInjectorImpl::MouseInjectorImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context,
                                     ProbeService::Stub &probe_service_stub)
    : grpc_context_{std::move(grpc_context)}
    , probe_service_stub_{probe_service_stub}
{}

AsyncResult<void> MouseInjectorImpl::single_action(ObjectId target_id, core::MouseAction action)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncMouseAction>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_object_id(target_id);
    request.set_mouse_action(::quite::proto::MouseAction::click);
    request.mutable_relative_point()->set_x(static_cast<float>(action.position.x));
    request.mutable_relative_point()->set_y(static_cast<float>(action.position.y));

    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, probe_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected(grpc_status2result(status));
    }
    co_return {};
}
} // namespace quite::proto
