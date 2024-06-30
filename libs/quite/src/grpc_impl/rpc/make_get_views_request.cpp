#include "make_get_views_request.hpp"
#include <agrpc/client_rpc.hpp>
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::GetViewsResponse> make_get_views_request(agrpc::GrpcContext &grpc_context,
                                                         proto::ProbeService::Stub &stub)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncGetViews>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    RPC::Request request;

    RPC::Response response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(status2error(status));
}

} // namespace quite::grpc_impl
