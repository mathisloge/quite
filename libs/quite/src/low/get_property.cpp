#include <quite/basic_remote_object.hpp>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <quite/low/get_property.hpp>
#include <spdlog/spdlog.h>
#include "../api_handle.hpp"
#include "../rpc/make_get_object_property_request.hpp"

namespace
{
LOGGER_IMPL(get_property)
}
namespace quite::low
{
exec::task<std::expected<value_handle, FindObjectErrorCode>> get_property(const BasicRemoteObject &obj,
                                                                          std::string_view property_name)
{
    SPDLOG_LOGGER_TRACE(logger_get_property(), "get property[{}] for object={}", property_name, obj.id());
    auto &&client = obj.api_handle()->object_client();
    const auto response =
        co_await make_get_object_property_request(client.context(), client.stub(), obj.id(), property_name);
    co_return response
        .and_then([&](auto &&reply) -> std::expected<value_handle, FindObjectErrorCode> {
            return value_handle{.value = response->value()};
        })
        .or_else([](auto &&error) -> std::expected<value_handle, FindObjectErrorCode> { return std::unexpected(FindObjectErrorCode::object_not_found); });
}
} // namespace quite::low
