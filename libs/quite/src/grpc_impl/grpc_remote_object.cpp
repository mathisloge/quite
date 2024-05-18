#include "grpc_remote_object.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "probe_client.hpp"
#include "rpc/make_get_object_property_request.hpp"

namespace
{
LOGGER_IMPL(grpc_remote_obj)
}
namespace quite::grpc_impl
{
GrpcRemoteObject::GrpcRemoteObject(ObjectId id, ProbeServiceHandle probe_service_handle)
    : RemoteObject{id},  probe_service_{std::move(probe_service_handle)}
{}

exec::task<std::expected<ValueHandle, FindObjectErrorCode>> GrpcRemoteObject::get_property(std::string_view property_name)
{
    SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "get property[{}] for object={}", property_name, id_);
    const auto response =
        co_await make_get_object_property_request(probe_service_->context(), probe_service_->stub(), id_, property_name);
    co_return response
        .and_then([&](auto &&reply) -> std::expected<ValueHandle, FindObjectErrorCode> {
            return ValueHandle{.value = response->value()};
        })
        .or_else([](auto &&error) -> std::expected<ValueHandle, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
}

} // namespace quite::grpc
