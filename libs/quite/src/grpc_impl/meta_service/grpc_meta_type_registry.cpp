#include "grpc_meta_type_registry.hpp"
#include <fmt/format.h>
#include <quite/logger.hpp>
#include "grpc_impl/probe_client.hpp"
#include "grpc_impl/rpc/make_meta_service_get_meta_object.hpp"
#include "meta/meta_type_storage.hpp"

DEFINE_LOGGER(grpc_meta_type_registry_logger);

using namespace quite::meta;
namespace quite::grpc_impl
{

//! TODO: save the objects already known and returns those instantly.

GrpcMetaTypeRegistry::GrpcMetaTypeRegistry(ProbeServiceHandle probe_service_handle)
    : probe_service_handle_{std::move(probe_service_handle)}
{}

AsyncResult<meta::Type> GrpcMetaTypeRegistry::resolve_type(meta::TypeId type_id)
{
    co_return std::unexpected(Error{
        .code = ErrorCode::unimplemented,
        .message = fmt::format("Got no meta type for type id '{}'", type_id),
    });
}

AsyncResult<meta::Type> GrpcMetaTypeRegistry::resolve_type(std::string_view type_name)
{
    LOG_DEBUG(grpc_meta_type_registry_logger, "Resolve type for '{}'", type_name);
    const auto meta_obj_response = co_await make_meta_service_get_meta_object(
        probe_service_handle_->context(), probe_service_handle_->meta_service_stub(), type_name);
    if (meta_obj_response.has_value() and not meta_obj_response->has_meta_type())
    {
        co_return std::unexpected(Error{
            .code = ErrorCode::failed_precondition,
            .message = fmt::format("Got no meta type for type '{}'", type_name),
        });
    }

    co_return meta_obj_response.transform([](const proto::MetaObjectResponse &obj_response) -> Type {
        if (obj_response.has_meta_type())
        {
            if (obj_response.meta_type().has_primitive_type())
            {
                //! TODO: make mapping
                return meta::Type{meta::PrimitiveType::type_int};
            }
        }
        return meta::Type{};
    });
}

} // namespace quite::grpc_impl