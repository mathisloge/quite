#include "quite/proto/probe/server.hpp"
#include <thread>
#include <exec/finally.hpp>
#include <quite/logger.hpp>
#include <quite/proto/health.grpc.pb.h>
#include <quite/proto/meta_service.grpc.pb.h>
#include <quite/proto/probe.grpc.pb.h>
#include "rpc_fetch_windows.hpp"
#include "rpc_find_object.hpp"
#include "rpc_invoke_method.hpp"
#include "rpc_meta_find_type.hpp"
#include "rpc_mouse_injection.hpp"
#include "rpc_object_properties.hpp"
#include "rpc_snapshot.hpp"
#include <grpc++/server_builder.h>
// needs to be after health.grpc.pb.h
#include <agrpc/health_check_service.hpp>

DEFINE_LOGGER(grpc_server_log);

namespace quite::proto
{
namespace
{
void run_server_until_stopped(std::stop_token stoken, std::string server_address)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    agrpc::GrpcContext grpc_context{builder.AddCompletionQueue()};

    ProbeService::AsyncService object_service;
    MetaService::AsyncService meta_service;

    builder.RegisterService(std::addressof(object_service));
    builder.RegisterService(std::addressof(meta_service));
    agrpc::add_health_check_service(builder);

    auto server = builder.BuildAndStart();
    agrpc::start_health_check_service(*server, grpc_context);

    stdexec::sender auto rpc_snapshot = make_rpc_snapshot(grpc_context, object_service);
    stdexec::sender auto rpc_find_object = make_rpc_find_object(grpc_context, object_service);
    stdexec::sender auto rpc_fetch_object_properties = make_rpc_fetch_object_properties(grpc_context, object_service);
    stdexec::sender auto rpc_fetch_windows = make_rpc_fetch_windows(grpc_context, object_service);
    stdexec::sender auto rpc_invoke_method = make_rpc_invoke_method(grpc_context, object_service);
    stdexec::sender auto rpc_mouse_injection = make_rpc_mouse_injection(grpc_context, object_service);
    stdexec::sender auto rpc_meta_find_type = make_rpc_meta_find_type(grpc_context, meta_service);

    stdexec::sender auto all_snd =
        exec::finally(stdexec::when_all(std::move(rpc_snapshot),
                                        std::move(rpc_find_object),
                                        std::move(rpc_fetch_object_properties),
                                        std::move(rpc_fetch_windows),
                                        std::move(rpc_invoke_method),
                                        std::move(rpc_mouse_injection),
                                        std::move(rpc_meta_find_type)),
                      stdexec::then(stdexec::just(), [&grpc_context] { grpc_context.work_finished(); }));

    stdexec::sync_wait(
        stdexec::when_all(std::move(all_snd), stdexec::then(stdexec::just(), [&grpc_context] { grpc_context.run(); })));
    LOG_INFO(grpc_server_log(), "gRPC server finished.");
}
} // namespace

struct Server::Impl
{
    Impl(std::string server_address)
        : grpc_runner_{std::bind(run_server_until_stopped, std::placeholders::_1, std::move(server_address))}
    {}
    std::jthread grpc_runner_;
};

Server::Server(std::string server_address)
    : impl_{std::make_unique<Impl>(std::move(server_address))}
{}

Server::Server(Server &&server) noexcept
    : impl_{std::move(server.impl_)}
{}

Server &Server::operator=(Server &&server) noexcept
{
    impl_ = std::move(server.impl_);
    return *this;
}

Server::~Server()
{}

} // namespace quite::proto
