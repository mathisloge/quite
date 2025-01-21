#include "make_create_snapshot_request.hpp"
#include <agrpc/client_rpc.hpp>
#include <quite/logger.hpp>
#include "error_helper.hpp"

DEFINE_LOGGER(rpc_snapshot_logger)

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

    RPC::Request request;
    request.set_object_id(id);
    RPC rpc{grpc_context};

    co_await rpc.start(stub, request, agrpc::use_sender);

    proto::ImageResponse final_response;
    bool do_read{true};
    while (do_read)
    {
        proto::ImageResponse response;
        do_read = co_await rpc.read(response, agrpc::use_sender);
        LOG_DEBUG(
            rpc_snapshot_logger(), "got snapshot chunk. Size={}. Has more to read={}", response.data().size(), do_read);

        std::copy(response.data().begin(), response.data().end(), std::back_inserter(*final_response.mutable_data()));
        if (response.has_metadata())
        {
            *final_response.mutable_metadata() = response.metadata();
        }
    }
    const auto status = co_await rpc.finish(agrpc::use_sender);
    LOG_DEBUG(rpc_snapshot_logger(), "snapshot finished with status={}", status.ok());
    if (status.ok())
    {
        LOG_DEBUG(rpc_snapshot_logger(), "got final snapshot. Size={}", final_response.data().size());
        co_return final_response;
    }
    co_return std::unexpected(status2error(status));
}

} // namespace quite::grpc_impl
