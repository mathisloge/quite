#include "process_application.hpp"
#include <quite/logger_macros.hpp>
#include <quite/create_logger.hpp>
#include <spawn.h>
#include <spdlog/spdlog.h>
#include "grpc_impl/probe_client.hpp"
#include "grpc_impl/rpc/make_find_object_request.hpp"
#include "grpc_impl/grpc_remote_object.hpp"

namespace
{
LOGGER_IMPL(process_application)
}

namespace quite
{
ProcessApplication::ProcessApplication(Context &context, const std::string &path_to_application)
    : process_{path_to_application}
    , stdout_pipe_{context.asioContext().get_executor(), process_.stdoutPipe()}
    , stderr_pipe_{context.asioContext().get_executor(), process_.stderrPipe()}
    , probe_handle_{std::make_shared<grpc_impl::ProbeClient>(context.grpcContext())}
{
    do_read();
}

ProcessApplication::~ProcessApplication() = default;

exec::task<std::expected<std::shared_ptr<RemoteObject>, FindObjectErrorCode>> ProcessApplication::find_object(std::string_view object_name)
{
    SPDLOG_LOGGER_TRACE(logger_process_application(), "Starting request with object_name={}", object_name);
    auto response = co_await make_find_object_request(probe_handle_->context(), probe_handle_->stub(), object_name);
    co_return response
        .and_then([&](auto &&reply) -> std::expected<std::shared_ptr<RemoteObject>, FindObjectErrorCode> {
            return std::make_shared<grpc_impl::GrpcRemoteObject>(reply.id(), probe_handle_);
        })
        .or_else([](auto &&error) -> std::expected<std::shared_ptr<RemoteObject>, FindObjectErrorCode> {
            return std::unexpected(FindObjectErrorCode::object_not_found);
        });
}

void ProcessApplication::do_read()
{
    // spdlog::trace("do_read");
    stdout_pipe_.async_read_some(asio::buffer(buffer), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            spdlog::debug("out {}", std::string_view{buffer.begin(), length});
            do_read();
        }
    });

    stderr_pipe_.async_read_some(asio::buffer(buffer), [this](std::error_code ec, std::size_t length) {
        if (!ec)
        {
            // spdlog::debug("err {}", std::string_view{buffer.begin(), length});
            do_read();
        }
    });
}
} // namespace quite
