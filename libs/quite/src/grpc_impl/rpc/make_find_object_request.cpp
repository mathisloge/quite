#include "make_find_object_request.hpp"
#include <agrpc/client_rpc.hpp>
#include "../grpc_value.hpp"
#include "error_helper.hpp"

namespace quite::grpc_impl
{
void write_query(proto::ObjectSearchQuery &proto_query, const ObjectQuery &query)
{
    if (query.container != nullptr)
    {
        write_query(*proto_query.mutable_parent(), *query.container);
    }
    for (auto &&[key, value] : query.properties)
    {
        proto_query.mutable_properties()->insert({key, convert(value)});
    }
}

AsyncResult<proto::ObjectReply> make_find_object_request(agrpc::GrpcContext &grpc_context,
                                                         proto::ProbeService::Stub &stub,
                                                         const ObjectQuery &query)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncFindObject>;
    grpc::ClientContext client_context;
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);

    proto::ObjectRequest request;
    auto &&proto_query = request.mutable_query();

    write_query(*proto_query, query);

    proto::ObjectReply response;
    const auto status = co_await RPC::request(grpc_context, stub, client_context, request, response);
    if (status.ok())
    {
        co_return response;
    }
    co_return std::unexpected(status2error(status));
}

} // namespace quite::grpc_impl
