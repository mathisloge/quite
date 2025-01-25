#include "make_invoke_method_request.hpp"
#include <agrpc/client_rpc.hpp>
#include "../grpc_value.hpp"
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::MethodCallResponse> make_invoke_method_request(agrpc::GrpcContext &grpc_context,
                                                                  proto::ProbeService::Stub &stub,
                                                                  ObjectId id,
                                                                  std::string method_name,
                                                                  std::span<const Value> parameters)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncInvokeMethod>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    RPC::Request request;

    request.set_object_id(id);
    auto *call = request.mutable_method_call();
    call->set_method_name(std::move(method_name));
    for (auto &&p : parameters)
    {
        *call->add_argument() = convert(p);
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
