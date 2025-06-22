#include "quite/proto/probe/server.hpp"
#include <thread>
#include <exec/env.hpp>
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
    stdexec::inplace_stop_source ssource_;
    ServiceHandle<IProbeHandler> probe_handler_;
    ServiceHandle<core::IMouseInjector> mouse_injector_;
    ServiceHandle<meta::MetaRegistry> meta_registry_;
    ServiceHandle<ValueRegistry> value_registry_;
    grpc::ServerBuilder builder_;
    std::unique_ptr<grpc::Server> grpc_server_; // server has to be destroyed after grpc_context_
    agrpc::GrpcContext grpc_context_{builder_.AddCompletionQueue()};
    std::jthread grpc_runner_;

  public:
    Impl(std::string server_address,
         ServiceHandle<IProbeHandler> probe_handler,
         ServiceHandle<core::IMouseInjector> mouse_injector,
         ServiceHandle<meta::MetaRegistry> meta_registry,
         ServiceHandle<ValueRegistry> value_registry)
        : probe_handler_{std::move(probe_handler)}
        , mouse_injector_{std::move(mouse_injector)}
        , meta_registry_{std::move(meta_registry)}
        , value_registry_{std::move(value_registry)}
        , grpc_runner_{[this, server_address = std::move(server_address)]() {
            run_server_until_stopped(std::move(server_address));
        }}
    {}

    ~Impl()
    {
        // wait for the grpc context to be running at least once otherwise we have race conditions in the
        // initialization.
        stdexec::sync_wait(stdexec::schedule(grpc_context_.get_scheduler()) | stdexec::then([this] {
                               // LOG_DEBUG(grpc_server_log(), "Shutting grpc server down...");
                               ssource_.request_stop();
                               grpc_server_->Shutdown(std::chrono::system_clock::now() + std::chrono::seconds{10});
                           }) |
                           stdexec::then([this] { grpc_server_->Wait(); }));
    }

  private:
    void run_server_until_stopped(std::string server_address)
    {

        builder_.AddListeningPort(server_address, grpc::InsecureServerCredentials());

        ProbeService::AsyncService object_service;
        MetaService::AsyncService meta_service;

        builder_.RegisterService(std::addressof(object_service));
        builder_.RegisterService(std::addressof(meta_service));
        agrpc::add_health_check_service(builder_);

        grpc_server_ = builder_.BuildAndStart();

        agrpc::start_health_check_service(*grpc_server_, grpc_context_);

        stdexec::sender auto rpc_snapshot = make_rpc_snapshot(grpc_context_, object_service, probe_handler_);
        stdexec::sender auto rpc_find_object =
            make_rpc_find_object(grpc_context_, object_service, probe_handler_, value_registry_);
        stdexec::sender auto rpc_fetch_object_properties =
            make_rpc_fetch_object_properties(grpc_context_, object_service, probe_handler_, value_registry_);
        stdexec::sender auto rpc_fetch_windows = make_rpc_fetch_windows(grpc_context_, object_service, probe_handler_);
        stdexec::sender auto rpc_invoke_method =
            make_rpc_invoke_method(grpc_context_, object_service, probe_handler_, value_registry_);
        stdexec::sender auto rpc_mouse_injection =
            make_rpc_mouse_injection(grpc_context_, object_service, mouse_injector_);
        stdexec::sender auto rpc_meta_find_type = make_rpc_meta_find_type(grpc_context_, meta_service, meta_registry_);

        auto stop_token_env = exec::write_env(stdexec::prop{stdexec::get_stop_token, ssource_.get_token()});
        stdexec::sender auto all_snd = stdexec::when_all(std::move(rpc_snapshot) | stop_token_env,
                                                         std::move(rpc_find_object) | stop_token_env,
                                                         std::move(rpc_fetch_object_properties) | stop_token_env,
                                                         std::move(rpc_fetch_windows) | stop_token_env,
                                                         std::move(rpc_invoke_method) | stop_token_env,
                                                         std::move(rpc_mouse_injection) | stop_token_env,
                                                         std::move(rpc_meta_find_type) | stop_token_env);

        grpc_context_.work_started();
        stdexec::sync_wait(stdexec::when_all(
            exec::finally(stdexec::starts_on(exec::inline_scheduler{}, stdexec::when_all(std::move(all_snd))),
                          stdexec::then(stdexec::just(),
                                        [&] {
                                            grpc_context_.work_finished();
                                            // LOG_DEBUG(grpc_server_log(), "grpc context finished work.");
                                        })),
            stdexec::then(stdexec::just(), [&] {
                LOG_DEBUG(grpc_server_log(), "Starting grpc context...");
                grpc_context_.run();
                // LOG_DEBUG(grpc_server_log(), "grpc context finished");
            })));

        // LOG_DEBUG(grpc_server_log(), "grpc thread finished");
    }
};

Server::Server(std::string server_address,
               ServiceHandle<IProbeHandler> probe_handler,
               ServiceHandle<core::IMouseInjector> mouse_injector,
               ServiceHandle<meta::MetaRegistry> meta_registry,
               ServiceHandle<ValueRegistry> value_registry)
    : impl_{std::make_unique<Impl>(std::move(server_address),
                                   std::move(probe_handler),
                                   std::move(mouse_injector),
                                   std::move(meta_registry),
                                   std::move(value_registry))}
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
