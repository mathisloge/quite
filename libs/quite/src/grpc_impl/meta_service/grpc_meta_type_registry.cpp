#include "grpc_meta_type_registry.hpp"
#include <fmt/format.h>
#include <quite/logger.hpp>
#include <quite/proto/meta_converters.hpp>
#include "grpc_impl/probe_client.hpp"
#include "grpc_impl/rpc/make_meta_find_type.hpp"

DEFINE_LOGGER(grpc_meta_type_registry_logger);

using namespace quite::meta;
namespace quite::grpc_impl
{

//! TODO: save the objects already known and returns those instantly.

GrpcMetaTypeRegistry::GrpcMetaTypeRegistry(ProbeServiceHandle probe_service_handle)
    : probe_service_handle_{std::move(probe_service_handle)}
{}

AsyncResult<meta::Type> GrpcMetaTypeRegistry::lookup_type(meta::TypeId type_id)
{
    LOG_DEBUG(grpc_meta_type_registry_logger(), "lookup type for '{}'", type_id);
    const auto meta_obj_response = co_await make_meta_find_type(
        probe_service_handle_->context(), probe_service_handle_->meta_service_stub(), type_id);
    if (not meta_obj_response.has_value() or not meta_obj_response->has_type())
    {
        co_return std::unexpected(Error{
            .code = ErrorCode::failed_precondition,
            .message = fmt::format("Got no meta type for type '{}'", type_id),
        });
    }
    co_return meta_obj_response.and_then([](const proto::MetaFindTypeResponse &response) -> Result<meta::Type> {
        auto &&meta_type = response.type();
        if (meta_type.has_primitive_type())
        {
            return proto::from_protocol(meta_type.primitive_type());
        }
        if (meta_type.has_enum_type())
        {
            return proto::from_protocol(meta_type.enum_type());
        }
        if (meta_type.has_list_type())
        {
            return proto::from_protocol(meta_type.list_type());
        }
        if (meta_type.has_map_type())
        {
            return proto::from_protocol(meta_type.map_type());
        }
        if (meta_type.has_object_type())
        {
            return proto::from_protocol(meta_type.object_type());
        }
        return make_error_result<meta::Type>(
            ErrorCode::failed_precondition,
            "Got a probe response but couldn't map protocol meta type to internal type.");
    });
}

} // namespace quite::grpc_impl
