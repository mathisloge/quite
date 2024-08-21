#include "grpc_remote_object.hpp"
#include <fmt/ranges.h>
#include <quite/logger.hpp>
#include "grpc_property.hpp"
#include "probe_client.hpp" // NOLINT
#include "rpc/make_create_snapshot_request.hpp"
#include "rpc/make_get_object_properties_request.hpp"
#include "rpc/make_mouse_click_request.hpp"

DEFINE_LOGGER(grpc_remote_object_logger);
namespace quite::grpc_impl
{
GrpcRemoteObject::GrpcRemoteObject(ObjectId id, ProbeServiceHandle probe_service_handle)
    : RemoteObject{id}
    , probe_service_{std::move(probe_service_handle)}
{}

AsyncResult<std::unordered_map<std::string, std::shared_ptr<Property>>> GrpcRemoteObject::fetch_properties(
    const std::vector<std::string_view> &properties)
{
    using RetVal = std::unordered_map<std::string, std::shared_ptr<Property>>;
    LOG_DEBUG(grpc_remote_object_logger,
              "get properties[{}] for object={}",
              fmt::format("{}", fmt::join(properties, ",")),
              id_);
    const auto response =
        co_await make_get_object_properties_request(probe_service_->context(), probe_service_->stub(), id_, properties);
    co_return response.and_then([&](auto && /*reply*/) -> Result<RetVal> {
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
    LOG_DEBUG(grpc_remote_object_logger, "get property[{}] for object={}", property_name, id_);

    // even though it is not really necessary to fetch the property here, it will get fetch, to verify that the property
    // exists. Otherwise an unexpected event is returned.
    const auto response = co_await make_get_object_properties_request(
        probe_service_->context(), probe_service_->stub(), id_, {property_name});
    co_return response.and_then(
        [&](const proto::GetObjectPropertiesResponse &reply) -> Result<std::shared_ptr<Property>> {
            auto it = reply.property_values().find(property_name);
            if (it == reply.property_values().end())
            {
                return std::unexpected(Error{ErrorCode::not_found, "Server did not return the expected property."});
            }
            return std::make_shared<GrpcProperty>(probe_service_, shared_from_this(), property_name, it->second);
        });
}

AsyncResult<void> GrpcRemoteObject::mouse_action()
{
    LOG_DEBUG(grpc_remote_object_logger, "mouse_action for object={}", id_);
    const auto response = co_await make_mouse_click_request(probe_service_->context(), probe_service_->stub(), id_);

    co_return response.and_then([&](auto && /*reply*/) -> Result<void> { return {}; });
}

AsyncResult<Image> GrpcRemoteObject::take_snapshot()
{
    auto response = co_await make_create_snapshot_request(probe_service_->context(), probe_service_->stub(), id_);
    co_return response.and_then([id = id_](auto &&image_response) -> Result<Image> {
        LOG_DEBUG(grpc_remote_object_logger, "Got image for obj={}", id);
        std::vector<std::byte> image_data;
        auto image_view = std::as_bytes(std::span{image_response.data().data(), image_response.data().size()});
        image_data.reserve(image_view.size());
        image_data.insert(image_data.begin(), image_view.begin(), image_view.end());
        return Image{std::move(image_data), image_response.metadata().width(), image_response.metadata().height(), 4};
    });
}
} // namespace quite::grpc_impl
