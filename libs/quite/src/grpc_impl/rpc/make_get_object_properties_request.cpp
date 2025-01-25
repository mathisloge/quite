#include "make_get_object_properties_request.hpp"
#include <agrpc/client_rpc.hpp>
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::GetObjectPropertiesResponse> make_get_object_properties_request(
    agrpc::GrpcContext &grpc_context,
    proto::ProbeService::Stub &stub,
    ObjectId id,
    std::span<const std::string> properties)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncGetObjectProperties>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    RPC::Request request;
    request.set_object_id(id);
    request.mutable_property_names()->Reserve(static_cast<int>(properties.size()));
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
    co_return std::unexpected(status2error(status));
}
} // namespace quite::grpc_impl
