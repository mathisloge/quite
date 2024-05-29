#include "make_create_snapshot_request.hpp"
#include <agrpc/client_rpc.hpp>
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::ImageResponse> make_create_snapshot_request(agrpc::GrpcContext &grpc_context,
                                                               proto::ProbeService::Stub &stub,
                                                               ObjectId id)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncCreateScreenshot>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    proto::ScreenshotRequest request;
    request.set_object_id(id);

    proto::ImageResponse response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(status2error(status));
}

} // namespace quite::grpc_impl
