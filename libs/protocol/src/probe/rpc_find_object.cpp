#include "rpc_find_object.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/value/object_query.hpp>

namespace quite::proto
{
namespace
{
ObjectQuery::PropertyMap convert_properties(const ::google::protobuf::Map<std::string, Value> &proto_properties)
{
    ObjectQuery::PropertyMap properties;
    for (auto &&prop : proto_properties)
    {
    }
}
} // namespace
exec::task<void> FindObjectRpcHandler::operator()(FindObjectRPC &rpc, const FindObjectRPC::Request &request)
{
    FindObjectRPC::Response response{};

    ObjectQuery object_query;
    const proto::ObjectSearchQuery *parent{&request.query()};
    while (parent->has_parent())
    {
        parent = &request.query().parent();
        auto parent_query = std::make_shared<ObjectQuery>();
        parent->properties();
    }
}

agrpc::detail::RPCHandlerSender<FindObjectRPC, FindObjectRpcHandler> find_object(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<FindObjectRPC>(grpc_context, service, FindObjectRpcHandler{});
}

} // namespace quite::proto
