#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/injectors/mouse_injector.hpp>
#include <quite/meta/meta_registry.hpp>
#include "probe_service.hpp"

namespace quite::proto
{
class ProbeClient final
{
  public:
    QUITE_DISABLE_COPY_MOVE(ProbeClient);
    explicit ProbeClient(std::string connection_url = "unix:///tmp/grpc_probe.sock");
    ~ProbeClient();

    IProbeService &probe_service();
    core::IMouseInjector &mouse_injector();
    meta::MetaRegistry &meta_registry();

    AsyncResult<void> wait_for_connected(std::chrono::seconds timeout);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::proto
