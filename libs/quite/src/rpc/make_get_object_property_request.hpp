#pragma once
#include <expected>
#include <agrpc/client_rpc.hpp>
#include <agrpc/grpc_context.hpp>
#include <exec/task.hpp>
#include <object/object.grpc.pb.h>
#include <quite/errors.hpp>
#include "quite/basic_remote_object.hpp"

namespace quite
{
static exec::task<std::expected<proto::PropertyResponse, FindObjectErrorCode>> make_get_object_property_request(
    agrpc::GrpcContext &grpc_context, proto::ObjectService::Stub &stub, ObjectId id, std::string_view property_name)
{
    using RPC = agrpc::ClientRPC<&proto::ObjectService::Stub::PrepareAsyncGetObjectProperty>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    proto::PropertyRequest request;
    request.set_id(id);
    *request.mutable_property_name() = property_name;

    proto::PropertyResponse response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(FindObjectErrorCode::object_not_found);

}
}
