#include "make_mouse_click_request.hpp"
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::VoidResponse> make_mouse_click_request(agrpc::GrpcContext &grpc_context,
                                                          proto::ProbeService::Stub &stub,
                                                          ObjectId id)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncMouseAction>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    proto::MouseActionRequest request;
    request.set_object_id(id);
    request.set_mouse_action(::quite::proto::MouseAction::click);

    proto::VoidResponse response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(status2error(status));
}
} // namespace quite::grpc_impl
