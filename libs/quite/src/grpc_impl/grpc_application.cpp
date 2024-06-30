#include "grpc_application.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "grpc_remote_object.hpp"
#include "probe_client.hpp"
#include "rpc/make_find_object_request.hpp"
#include "rpc/make_get_views_request.hpp"

namespace
{
LOGGER_IMPL(grpc_application)
}

namespace quite::grpc_impl
{
GrpcApplication::GrpcApplication(Context &context)
    : probe_handle_{std::make_shared<grpc_impl::ProbeClient>(context.grpcContext())}
{}

AsyncResult<std::shared_ptr<RemoteObject>> GrpcApplication::find_object(std::string_view object_name)
{
    SPDLOG_LOGGER_TRACE(logger_grpc_application(), "Starting request with object_name={}", object_name);
    auto response =
        co_await grpc_impl::make_find_object_request(probe_handle_->context(), probe_handle_->stub(), object_name);
    co_return response.and_then([&](proto::ObjectReply &reply) -> Result<std::shared_ptr<RemoteObject>> {
        return std::make_shared<GrpcRemoteObject>(reply.object_id(), probe_handle_);
    });
}

AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> GrpcApplication::get_views()
{
    SPDLOG_LOGGER_TRACE(logger_grpc_application(), "Requesting top level views from {}", "[TODO:APPNAME]");
    auto response = co_await grpc_impl::make_get_views_request(probe_handle_->context(), probe_handle_->stub());
    co_return response.and_then(
        [&](proto::GetViewsResponse &reply) -> Result<std::vector<std::shared_ptr<RemoteObject>>> {
            std::vector<std::shared_ptr<RemoteObject>> views;
            views.reserve(reply.object_id_size());
            for (auto &&obj : reply.object_id())
            {
                views.emplace_back(std::make_shared<grpc_impl::GrpcRemoteObject>(obj, probe_handle_));
            }
            return views;
        });
}

} // namespace quite::grpc_impl
