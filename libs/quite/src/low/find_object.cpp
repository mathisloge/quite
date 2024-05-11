#include <quite/application.hpp>
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <quite/low/find_object.hpp>
#include <spdlog/spdlog.h>
#include "../api_handle.hpp"
#include "../remote_object.hpp"
#include "../rpc/make_find_object_request.hpp"

namespace
{
LOGGER_IMPL(find_object)
}
namespace quite::low
{
exec::task<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> find_object(
    const Application &app, std::string_view object_name)
{
    SPDLOG_LOGGER_TRACE(logger_find_object(), "Starting request with object_name={}", object_name);
    auto &&client = app.api_handle()->object_client();
    auto response = co_await make_find_object_request(client.context(), client.stub(), object_name);
    co_return response
        .and_then([&](auto &&reply) -> std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode> {
            return std::make_shared<RemoteObject>(app.api_handle(), reply.id(), reply.type_name());
        })
        .or_else([](auto &&error) -> std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
}
} // namespace quite::low
