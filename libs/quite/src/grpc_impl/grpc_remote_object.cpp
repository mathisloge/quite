#include "grpc_remote_object.hpp"
#include <fmt/ranges.h>
#include <quite/logger.hpp>
#include "grpc_impl/grpc_value.hpp"
#include "grpc_property.hpp"
#include "probe_client.hpp" // NOLINT
#include "rpc/make_create_snapshot_request.hpp"
#include "rpc/make_get_object_properties_request.hpp"
#include "rpc/make_invoke_method_request.hpp"
#include "rpc/make_mouse_click_request.hpp"

DEFINE_LOGGER(grpc_remote_object_logger);
namespace quite::grpc_impl
{
GrpcRemoteObject::GrpcRemoteObject(ObjectId id, meta::TypeId type_id, ProbeServiceHandle probe_service_handle)
    : RemoteObject{id}
    , type_id_{type_id}
    , probe_service_{std::move(probe_service_handle)}
{}

meta::TypeId GrpcRemoteObject::type_id() const
{
    return type_id_;
}

AsyncResult<std::unordered_map<std::string, std::shared_ptr<Property>>> GrpcRemoteObject::fetch_properties(
    std::span<const std::string> properties)
{
    using RetVal = std::unordered_map<std::string, std::shared_ptr<Property>>;
    LOG_DEBUG(grpc_remote_object_logger(),
              "get properties[{}] for object={}",
              fmt::format("{}", fmt::join(properties, ",")),
              id());
    const auto response = co_await make_get_object_properties_request(
        probe_service_->context(), probe_service_->stub(), id(), properties);
    co_return response.transform([&](auto && /*reply*/) -> RetVal {
        RetVal values;
        for (auto &&val : response->property_values())
        {
            values.emplace(val.first,
                           std::make_shared<GrpcProperty>(probe_service_, shared_from_this(), val.first, val.second));
        }
        return values;
    });
}

AsyncResult<std::shared_ptr<Property>> GrpcRemoteObject::property(std::string property_name)
{
    LOG_DEBUG(grpc_remote_object_logger(), "get property[{}] for object={}", property_name, id());

    // even though it is not really necessary to fetch the property here, it will get fetch, to verify that the property
    // exists. Otherwise an unexpected event is returned.
    const auto requested_property = std::array{std::string{property_name}};
    const auto response = co_await make_get_object_properties_request(
        probe_service_->context(), probe_service_->stub(), id(), requested_property);
    co_return response.and_then(
        [&](const proto::GetObjectPropertiesResponse &reply) -> Result<std::shared_ptr<Property>> {
            auto it = reply.property_values().find(property_name);
            if (it == reply.property_values().end())
            {
                return std::unexpected(Error{ErrorCode::not_found, "Server did not return the expected property."});
            }
            return std::make_shared<GrpcProperty>(
                probe_service_, shared_from_this(), std::move(property_name), it->second);
        });
}

AsyncResult<void> GrpcRemoteObject::mouse_action()
{
    LOG_DEBUG(grpc_remote_object_logger(), "mouse_action for object={}", id());
    const auto response = co_await make_mouse_click_request(probe_service_->context(), probe_service_->stub(), id());

    co_return response.transform([&](auto && /*reply*/) -> void {});
}

AsyncResult<Image> GrpcRemoteObject::take_snapshot()
{
    auto response = co_await make_create_snapshot_request(probe_service_->context(), probe_service_->stub(), id());
    co_return response.transform([id = id()](auto &&image_response) -> Image {
        LOG_DEBUG(grpc_remote_object_logger(), "Got image for obj={}", id);
        std::vector<std::byte> image_data;
        auto image_view = std::as_bytes(std::span{image_response.data().data(), image_response.data().size()});
        image_data.reserve(image_view.size());
        image_data.insert(image_data.begin(), image_view.begin(), image_view.end());
        return Image{std::move(image_data), image_response.metadata().width(), image_response.metadata().height(), 4};
    });
}

AsyncResult<void> GrpcRemoteObject::invoke_method(std::string method_name)
{
    auto response = co_await make_invoke_method_request(
        probe_service_->context(), probe_service_->stub(), id(), std::move(method_name), {});
    LOG_DEBUG(grpc_remote_object_logger(), "Got method invoke result: {}", response.has_value());
    if (response.has_value())
    {
        if (response->has_return_value() and response->return_value().has_value())
        {
            auto return_val = convert(response->return_value().value(), probe_service_);
            if (return_val.has_value())
            {
                LOG_DEBUG(grpc_remote_object_logger(), "Has return value: {}", fmt::format("{}", *return_val));
            }
        }
    }
    else
    {
        LOG_DEBUG(grpc_remote_object_logger(), "Error: {}", fmt::format("{}", response.error()));
    }
    co_return {};
}
} // namespace quite::grpc_impl
