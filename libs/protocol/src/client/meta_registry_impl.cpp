#include "meta_registry_impl.hpp"
#include <quite/logger.hpp>
#include "configure_client_context.hpp"
#include "error_helper.hpp"
#include "meta_converters.hpp"

DEFINE_LOGGER(meta_registry);

namespace quite::proto
{

MetaRegistryImpl::MetaRegistryImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context,
                                   MetaService::Stub &meta_service_stub)
    : grpc_context_{std::move(grpc_context)}
    , meta_service_stub_{meta_service_stub}
{}

AsyncResult<meta::Type> MetaRegistryImpl::lookup_type(meta::TypeId type_id)
{
    LOG_DEBUG(meta_registry(), "lookup type for '{}'", type_id);

    using RPC = agrpc::ClientRPC<&proto::MetaService::Stub::PrepareAsyncFindType>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_type_id(type_id);

    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, meta_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected(grpc_status2result(status));
    }
    if (not response.has_type())
    {
        co_return std::unexpected(Error{
            .code = ErrorCode::failed_precondition,
            .message = fmt::format("Got no meta type for type '{}'", type_id),
        });
    }

    auto &&meta_type = response.type();
    if (meta_type.has_primitive_type())
    {
        co_return from_protocol(meta_type.primitive_type());
    }
    if (meta_type.has_enum_type())
    {
        co_return from_protocol(meta_type.enum_type());
    }
    if (meta_type.has_list_type())
    {
        co_return from_protocol(meta_type.list_type());
    }
    if (meta_type.has_map_type())
    {
        co_return from_protocol(meta_type.map_type());
    }
    if (meta_type.has_object_type())
    {
        co_return from_protocol(meta_type.object_type());
    }
    co_return make_error_result<meta::Type>(
        ErrorCode::failed_precondition, "Got a probe response but couldn't map protocol meta type to internal type.");
}
} // namespace quite::proto
