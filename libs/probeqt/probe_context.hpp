#pragma once
#include <thread>
#include <agrpc/grpc_context.hpp>
#include <grpcpp/server_builder.h>
#include <private/qhooks_p.h>
#include <quite/proto/probe.grpc.pb.h>
#include "injector/mouse_injector.hpp"
#include "method_invoker.hpp"

namespace quite::probe
{
class ProbeContext final
{
  public:
    ProbeContext(grpc::ServerBuilder builder = {});
    ~ProbeContext();

    void qt_hook_add_object(QObject *q);
    void qt_hook_remove_object(QObject *q);
    void qt_hook_startup();

  private:
    void request_exit();
    void install_qt_hooks();
    void install_application_hooks();

  private:
    std::jthread grpc_runner_;
    agrpc::GrpcContext grpc_context_;
    std::unique_ptr<grpc::Server> grpc_server_;
    quite::ObjectTracker object_tracker_;
    quite::probe::MouseInjector mouse_injector_;
    quite::probe::MethodInvoker method_invoker_;
    quite::proto::ProbeService::AsyncService object_service_;

    QHooks::AddQObjectCallback next_add_qobject_hook_{nullptr};
    QHooks::RemoveQObjectCallback next_remove_qobject_hook_{nullptr};
    QHooks::StartupCallback next_startup_hook_{nullptr};
};
} // namespace quite::probe
