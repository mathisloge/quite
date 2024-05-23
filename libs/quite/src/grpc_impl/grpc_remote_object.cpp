#include "grpc_remote_object.hpp"
#include <ranges>
#include <quite/create_logger.hpp>
#include <quite/image.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "probe_client.hpp"
#include "rpc/make_create_snapshot_request.hpp"
#include "rpc/make_get_object_properties_request.hpp"
#include "rpc/make_mouse_click_request.hpp"

namespace
{
LOGGER_IMPL(grpc_remote_obj)
}
namespace quite::grpc_impl
{
GrpcRemoteObject::GrpcRemoteObject(ObjectId id, ProbeServiceHandle probe_service_handle)
    : RemoteObject{id}
    , probe_service_{std::move(probe_service_handle)}
{}

exec::task<Result<std::vector<Property>>> GrpcRemoteObject::fetch_properties(
    const std::vector<std::string_view> &properties)
{
    SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "get properties[{}] for object={}", fmt::join(properties, ","), id_);
    const auto response =
        co_await make_get_object_properties_request(probe_service_->context(), probe_service_->stub(), id_, properties);
    co_return response.and_then([&](auto &&reply) -> Result<std::vector<Property>> {
        std::vector<Property> values;
        std::ranges::copy(std::views::transform(response->property_values(),
                                                [](auto &&value) {
                                                    return Property{.name = value.first,
                                                                    .value = ValueHandle{.value = value.second}};
                                                }),
                          std::back_inserter(values));
        return values;
    });
}

exec::task<Result<void>> GrpcRemoteObject::mouse_action()
{
    SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "mouse_action for object={}", id_);
    const auto response = co_await make_mouse_click_request(probe_service_->context(), probe_service_->stub(), id_);

    co_return response.and_then([&](auto &&reply) -> Result<void> { return {}; });
}

exec::task<Result<Image>> GrpcRemoteObject::take_snapshot()
{
    auto response = co_await make_create_snapshot_request(probe_service_->context(), probe_service_->stub(), id_);
    co_return response.and_then([id = id_](auto &&image_response) -> Result<Image> {
        SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "Got image for obj={}", id);
        std::vector<std::byte> image_data;
        auto image_view = std::as_bytes(std::span{image_response.data().data(), image_response.data().size()});
        image_data.reserve(image_view.size());
        image_data.insert(image_data.begin(), image_view.begin(), image_view.end());
        return Image{std::move(image_data), image_response.metadata().width(), image_response.metadata().height(), 4};
    });
}
} // namespace quite::grpc_impl
