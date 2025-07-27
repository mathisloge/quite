#include "grpc_probe.hpp"
#include <boost/asio/steady_timer.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <quite/logger.hpp>
#include "grpc_remote_object.hpp"

#include <fmt/base.h>

DEFINE_LOGGER(grpc_app_logger)

namespace quite::client
{
GrpcProbe::GrpcProbe(manager::ProcessHandle process, proto::Client &client, std::string connection_uri)
    : BasicProbe{std::move(process)}
    , client_{client.create_probe_client(value_converter_, std::move(connection_uri))}
{
    value_converter_->set_client(client_);
}

AsyncResult<void> GrpcProbe::wait_for_started(std::chrono::seconds timeout)
{
    co_return co_await client_->wait_for_connected(timeout);
}

AsyncResult<std::shared_ptr<RemoteObject>> GrpcProbe::find_object(ObjectQuery query)
{
    LOG_DEBUG(grpc_app_logger(), "Starting request with object_name={}", fmt::format("{}", query));
    const auto object_result = co_await client_->probe_service().find_object(std::move(query));
    co_return object_result.and_then([this](ObjectReference object_ref) -> Result<std::shared_ptr<RemoteObject>> {
        return std::make_shared<GrpcRemoteObject>(object_ref, client_);
    });
}

AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> GrpcProbe::get_views()
{
    LOG_TRACE_L1(grpc_app_logger(), "Requesting top level views from {}", "[TODO:APPNAME]");
    auto response = co_await client_->probe_service().query_top_level_views();
    co_return response.and_then(
        [this](const std::vector<ObjectReference> &refs) -> Result<std::vector<std::shared_ptr<RemoteObject>>> {
            std::vector<std::shared_ptr<RemoteObject>> views;
            views.reserve(refs.size());
            for (auto &&obj : refs)
            {
                views.emplace_back(std::make_shared<GrpcRemoteObject>(obj, client_));
            }
            return views;
        });
}

meta::MetaRegistry &GrpcProbe::meta_registry()
{
    return client_->meta_registry();
}

} // namespace quite::client
