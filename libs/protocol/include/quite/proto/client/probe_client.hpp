#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/injectors/mouse_injector.hpp>
#include <quite/meta/meta_registry.hpp>
#include "probe_service.hpp"
#include "quite/quite_protocol_export.hpp"

namespace quite::proto
{
class QUITE_PROTOCOL_EXPORT ProbeClient
{
  public:
    QUITE_DISABLE_COPY_MOVE(ProbeClient);
    ProbeClient();
    virtual ~ProbeClient();

    virtual IProbeService &probe_service() = 0;
    virtual core::IMouseInjector &mouse_injector() = 0;
    virtual meta::MetaRegistry &meta_registry() = 0;
    virtual AsyncResult<void> wait_for_connected(std::chrono::seconds timeout) = 0;
};
} // namespace quite::proto
