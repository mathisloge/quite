#include "grpc_application.hpp"
#include <quite/logger.hpp>
#include "grpc_remote_object.hpp"
#include "probe_client.hpp"
#include "rpc/make_exit_request.hpp"
#include "rpc/make_find_object_request.hpp"
#include "rpc/make_get_views_request.hpp"

DEFINE_LOGGER(grpc_app_logger)

namespace quite::grpc_impl
{
GrpcApplication::GrpcApplication(Context &context)
    : probe_handle_{std::make_shared<grpc_impl::ProbeClient>(context.grpcContext())}
{}

AsyncResult<std::shared_ptr<RemoteObject>> GrpcApplication::find_object(const ObjectQuery &query)
{
    LOG_TRACE_L1(grpc_app_logger, "Starting request with object_name={}", fmt::format("{}", query));
    const auto response =
        co_await grpc_impl::make_find_object_request(probe_handle_->context(), probe_handle_->stub(), query);
    co_return response.and_then([&](const proto::ObjectReply &reply) -> Result<std::shared_ptr<RemoteObject>> {
        return std::make_shared<GrpcRemoteObject>(reply.object_id(), probe_handle_);
    });
}

AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> GrpcApplication::get_views()
{
    LOG_TRACE_L1(grpc_app_logger, "Requesting top level views from {}", "[TODO:APPNAME]");
    const auto response = co_await grpc_impl::make_get_views_request(probe_handle_->context(), probe_handle_->stub());
    co_return response.and_then(
        [&](const proto::GetViewsResponse &reply) -> Result<std::vector<std::shared_ptr<RemoteObject>>> {
            std::vector<std::shared_ptr<RemoteObject>> views;
            views.reserve(reply.object_id_size());
            for (auto &&obj : reply.object_id())
            {
                views.emplace_back(std::make_shared<grpc_impl::GrpcRemoteObject>(obj, probe_handle_));
            }
            return views;
        });
}

AsyncResult<void> GrpcApplication::exit()
{
    LOG_TRACE_L1(grpc_app_logger, "Request exiting application {}", "[TODO:APPNAME]");
    const auto response = co_await grpc_impl::make_exit_request(probe_handle_->context(), probe_handle_->stub());
    co_return response.and_then([&](const proto::ExitReponse & /*reply*/) -> Result<void> { return {}; });
}

} // namespace quite::grpc_impl
