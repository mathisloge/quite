#include "grpc_application.hpp"
#include <boost/asio/steady_timer.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <quite/logger.hpp>
#include "grpc_remote_object.hpp"

DEFINE_LOGGER(grpc_app_logger)

namespace quite
{
GrpcApplication::GrpcApplication(Context &context)
    : client_{std::make_shared<proto::ProbeClient>()}
{}

AsyncResult<void> GrpcApplication::wait_for_started(std::chrono::seconds timeout)
{
    co_return co_await client_->wait_for_connected(timeout);
}

AsyncResult<std::shared_ptr<RemoteObject>> GrpcApplication::find_object(ObjectQuery query)
{
    LOG_DEBUG(grpc_app_logger(), "Starting request with object_name={}", fmt::format("{}", query));
    const auto object_result = co_await client_->probe_service().find_object(std::move(query));
    co_return object_result.and_then([this](ObjectReference object_ref) -> Result<std::shared_ptr<RemoteObject>> {
        return std::make_shared<GrpcRemoteObject>(object_ref, client_);
    });
}

AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> GrpcApplication::get_views()
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

AsyncResult<void> GrpcApplication::exit()
{
    co_return {};
}

meta::MetaRegistry &GrpcApplication::meta_registry()
{
    return client_->meta_registry();
}

} // namespace quite
