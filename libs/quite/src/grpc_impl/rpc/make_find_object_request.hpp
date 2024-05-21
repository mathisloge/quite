#pragma once
#include <expected>
#include <agrpc/client_rpc.hpp>
#include <agrpc/grpc_context.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/errors.hpp>

namespace quite
{
static exec::task<std::expected<proto::ObjectReply, FindObjectErrorCode>> make_find_object_request(
    agrpc::GrpcContext &grpc_context, proto::ProbeService::Stub &stub, std::string_view object_name)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncFindObject>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    proto::ObjectRequest request;
    request.mutable_query()->mutable_properties()->emplace("objectName", std::string{object_name});

    proto::ObjectReply response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(FindObjectErrorCode::object_not_found);
}

} // namespace quite
