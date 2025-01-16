#include "make_meta_service_get_meta_object.hpp"
#include <agrpc/client_rpc.hpp>
#include "configure_client_context.hpp"
#include "error_helper.hpp"

namespace quite::grpc_impl
{
AsyncResult<proto::MetaObjectResponse> make_meta_service_get_meta_object(agrpc::GrpcContext &grpc_context,
                                                                         proto::MetaService::Stub &stub,
                                                                         meta::TypeId type_id)
{
    using RPC = agrpc::ClientRPC<&proto::MetaService::Stub::PrepareAsyncGetMetaObject>;
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
