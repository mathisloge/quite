#pragma once
#include <expected>
#include <agrpc/client_rpc.hpp>
#include <agrpc/grpc_context.hpp>
#include <exec/task.hpp>
#include <quite/errors.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/remote_object.hpp>

namespace quite
{
static exec::task<std::expected<proto::GetObjectPropertiesResponse, FindObjectErrorCode>> make_get_object_properties_request(
    agrpc::GrpcContext &grpc_context,
    proto::ProbeService::Stub &stub,
    ObjectId id,
    const std::vector<std::string_view> &properties)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncGetObjectProperties>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    RPC::Request request;
    request.set_object_id(id);
    request.mutable_property_names()->Reserve(properties.size());
    for (auto property_name : properties)
    {
        request.mutable_property_names()->Add(std::string{property_name});
    }

    RPC::Response response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(FindObjectErrorCode::object_not_found);
}
} // namespace quite
