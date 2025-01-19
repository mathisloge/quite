#include "make_meta_find_type.hpp"
#include <agrpc/client_rpc.hpp>
#include "configure_client_context.hpp"
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::MetaFindTypeResponse> make_meta_find_type(agrpc::GrpcContext &grpc_context,
                                                             proto::MetaService::Stub &stub,
                                                             meta::TypeId type_id)
{
    using RPC = agrpc::ClientRPC<&proto::MetaService::Stub::PrepareAsyncFindType>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_type_id(type_id);

    RPC::Response response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected(status2error(status));
    }
    co_return response;
}
} // namespace quite::grpc_impl
