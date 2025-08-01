// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "grpc_remote_object.hpp"
#include <fmt/ranges.h>
#include <quite/logger.hpp>
#include "grpc_property.hpp"

DEFINE_LOGGER(grpc_remote_object_logger);
namespace quite::client
{
GrpcRemoteObject::GrpcRemoteObject(ObjectReference reference, std::shared_ptr<proto::ProbeClient> client)
    : RemoteObject{reference.object_id}
    , client_{std::move(client)}
    , type_id_{reference.type_id}
{}

meta::TypeId GrpcRemoteObject::type_id() const
{
    return type_id_;
}

AsyncResult<std::unordered_map<std::string, std::shared_ptr<Property>>> GrpcRemoteObject::fetch_properties(
    std::vector<std::string> properties)
{
    using RetVal = std::unordered_map<std::string, std::shared_ptr<Property>>;
    LOG_DEBUG(grpc_remote_object_logger(),
              "get properties[{}] for object={}",
              fmt::format("{}", fmt::join(properties, ",")),
              id());
    const auto result = co_await client_->probe_service().get_object_properties(id(), std::move(properties));
    co_return result.transform([this](auto &&properties) -> RetVal {
        RetVal values;
        for (auto &&[key, value] : properties)
        {
            values.emplace(key, std::make_shared<GrpcProperty>(shared_from_this(), key, value));
        }
        return values;
    });
}

AsyncResult<std::shared_ptr<Property>> GrpcRemoteObject::property(std::string property_name)
{
    LOG_DEBUG(grpc_remote_object_logger(), "get property[{}] for object={}", property_name, id());

    auto response = co_await fetch_property(property_name);
    co_return response.and_then([this, &property_name](auto &&value) -> Result<std::shared_ptr<Property>> {
        return std::make_shared<GrpcProperty>(
            shared_from_this(), std::move(property_name), std::forward<decltype(value)>(value));
    });
}

AsyncResult<void> GrpcRemoteObject::write_property(std::string property_name, entt::meta_any value)
{
    auto response =
        co_await client_->probe_service().set_object_property(id(), std::move(property_name), std::move(value));
    co_return response;
}

AsyncResult<entt::meta_any> GrpcRemoteObject::fetch_property(std::string property_name)
{
    std::vector<std::string> gcc13_workaround{property_name}; // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=115660
    auto response = co_await client_->probe_service().get_object_properties(id(), std::move(gcc13_workaround));
    co_return response.and_then([this, &property_name](auto &&properties) -> Result<entt::meta_any> {
        auto it = properties.find(property_name);
        if (it == properties.end())
        {
            return make_error_result(ErrorCode::not_found, "Server did not return the expected property.");
        }
        return it->second;
    });
}

AsyncResult<void> GrpcRemoteObject::mouse_action()
{
    LOG_DEBUG(grpc_remote_object_logger(), "mouse_action for object={}", id());
    co_return co_await client_->mouse_injector().single_action(
        id(), core::MouseAction{.button = core::MouseButton::left, .trigger = core::MouseTrigger::click});
}

AsyncResult<Image> GrpcRemoteObject::take_snapshot()
{
    co_return co_await client_->probe_service().take_snapshot(id());
}

AsyncResult<void> GrpcRemoteObject::invoke_method(std::string method_name)
{
    LOG_DEBUG(grpc_remote_object_logger(), "invoke method: {}", method_name);
    auto response = co_await client_->probe_service().invoke_method(id(), std::move(method_name), {});

    if (response.has_value())
    {
        if (*response)
        {
            LOG_DEBUG(grpc_remote_object_logger(), "Has return value: {}", response->type().info().name());
        }
        co_return {};
    }
    co_return std::unexpected{std::move(response.error())};
}
} // namespace quite::client
