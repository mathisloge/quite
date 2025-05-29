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
class Server::Impl
{
    std::jthread grpc_runner_;
    std::unique_ptr<grpc::Server> grpc_server_;
    std::unique_ptr<agrpc::GrpcContext> grpc_context_;

  public:
    Impl(std::string server_address)
        : grpc_runner_{[this, server_address = std::move(server_address)](std::stop_token stoken) {
            run_server_until_stopped(std::move(stoken), std::move(server_address));
        }}
    {}

    ~Impl()
    {
        if (grpc_server_ != nullptr)
        {
            grpc_server_->Shutdown();
            grpc_context_ = nullptr; // Ensure the context is destroyed before the server
            grpc_server_->Wait();
        }
    }

  private:
    template <class Sender>
    void run_grpc_context_for_sender(agrpc::GrpcContext &grpc_context, Sender &&sender)
    {
        stdexec::sender auto all_snd =
            exec::finally(std::forward<Sender>(sender),
                          stdexec::then(stdexec::just(), [&grpc_context] { grpc_context.work_finished(); }));

        grpc_context.work_started();
        stdexec::sync_wait(
            stdexec::when_all(std::move(all_snd), stdexec::just() | stdexec::then([&]() { grpc_context.run(); })));
    }

    void run_server_until_stopped(std::stop_token stoken, std::string server_address)
    {
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

        ProbeService::AsyncService object_service;
        MetaService::AsyncService meta_service;

        builder.RegisterService(std::addressof(object_service));
        builder.RegisterService(std::addressof(meta_service));
        grpc_context_ = std::make_unique<agrpc::GrpcContext>(builder.AddCompletionQueue());
        agrpc::add_health_check_service(builder);

        grpc_server_ = builder.BuildAndStart();

        agrpc::start_health_check_service(*grpc_server_, *grpc_context_);

        stdexec::sender auto rpc_snapshot = make_rpc_snapshot(*grpc_context_, object_service);
        stdexec::sender auto rpc_find_object = make_rpc_find_object(*grpc_context_, object_service);
        stdexec::sender auto rpc_fetch_object_properties =
            make_rpc_fetch_object_properties(*grpc_context_, object_service);
        stdexec::sender auto rpc_fetch_windows = make_rpc_fetch_windows(*grpc_context_, object_service);
        stdexec::sender auto rpc_invoke_method = make_rpc_invoke_method(*grpc_context_, object_service);
        stdexec::sender auto rpc_mouse_injection = make_rpc_mouse_injection(*grpc_context_, object_service);
        stdexec::sender auto rpc_meta_find_type = make_rpc_meta_find_type(*grpc_context_, meta_service);

        // only start the server if the stop has not been requested
        if (not stoken.stop_requested())
        {
            run_grpc_context_for_sender(*grpc_context_,
                                        stdexec::when_all(std::move(rpc_snapshot),
                                                          std::move(rpc_find_object),
                                                          std::move(rpc_fetch_object_properties),
                                                          std::move(rpc_fetch_windows),
                                                          std::move(rpc_invoke_method),
                                                          std::move(rpc_mouse_injection),
                                                          std::move(rpc_meta_find_type)));
        }
    }
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

Server::~Server() = default;

} // namespace quite::proto
