#pragma once
#include <expected>
#include <agrpc/client_rpc.hpp>
#include <agrpc/grpc_context.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/errors.hpp>
#include "quite/basic_remote_object.hpp"

namespace quite
{
static exec::task<std::expected<proto::ImageResponse, FindObjectErrorCode>> make_create_screenshot_request(
    agrpc::GrpcContext &grpc_context, proto::ProbeService::Stub &stub, ObjectId id)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncCreateScreenshot>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    proto::ScreenshotRequest request;
    request.set_id(id);

    proto::ImageResponse response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(FindObjectErrorCode::object_not_found);
}

} // namespace quite
