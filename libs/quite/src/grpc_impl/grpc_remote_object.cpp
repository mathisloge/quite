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

exec::task<std::expected<std::vector<Property>, FindObjectErrorCode>> GrpcRemoteObject::fetch_properties(
    const std::vector<std::string_view> &properties)
{
    SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "get properties[{}] for object={}", fmt::join(properties, ","), id_);
    const auto response =
        co_await make_get_object_properties_request(probe_service_->context(), probe_service_->stub(), id_, properties);
    co_return response
        .and_then([&](auto &&reply) -> std::expected<std::vector<Property>, FindObjectErrorCode> {
            std::vector<Property> values;
            std::ranges::copy(std::views::transform(response->property_values(),
                                                    [](auto &&value) {
                                                        return Property{.name = value.first,
                                                                        .value = ValueHandle{.value = value.second}};
                                                    }),
                              std::back_inserter(values));
            return values;
        })
        .or_else([](auto &&error) -> std::expected<std::vector<Property>, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
}

exec::task<std::expected<void, FindObjectErrorCode>> GrpcRemoteObject::mouse_action()
{
    SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "mouse_action for object={}", id_);
    const auto response = co_await make_mouse_click_request(probe_service_->context(), probe_service_->stub(), id_);

    co_return response.and_then([&](auto &&reply) -> std::expected<void, FindObjectErrorCode> { return {}; })
        .or_else([](auto &&error) -> std::expected<void, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
}

exec::task<std::expected<Image, FindObjectErrorCode>> GrpcRemoteObject::take_snapshot()
{
    auto response = co_await make_create_snapshot_request(probe_service_->context(), probe_service_->stub(), id_);
    if (response.has_value())
    {
        SPDLOG_LOGGER_TRACE(logger_grpc_remote_obj(), "Got image for obj={}", id_);
        std::vector<std::byte> image_data;
        auto image_view = std::as_bytes(std::span{response->data().data(), response->data().size()});
        image_data.reserve(image_view.size());
        image_data.insert(image_data.begin(), image_view.begin(), image_view.end());
        co_return Image{std::move(image_data), response->metadata().width(), response->metadata().height(), 4};
    }
    co_return std::unexpected(FindObjectErrorCode::object_not_found);
}
} // namespace quite::grpc_impl
