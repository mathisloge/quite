#pragma once
#include <memory>
#include <string>
#include <entt/locator/locator.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/service_handle.hpp>
#include "quite/quite_protocol_export.hpp"
namespace quite
{
class ValueRegistry;
}
namespace quite::core
{
class IMouseInjector;
}
namespace quite::meta
{
class MetaRegistry;
}

namespace quite::proto
{
class IProbeHandler;

class QUITE_PROTOCOL_EXPORT Server final
{
  public:
    QUITE_DISABLE_COPY(Server);
    Server(std::string server_address,
           ServiceHandle<IProbeHandler> probe_handler,
           ServiceHandle<core::IMouseInjector> mouse_injector,
           ServiceHandle<meta::MetaRegistry> meta_registry,
           ServiceHandle<ValueRegistry> value_registry);
    Server(Server &&server) noexcept;
    Server &operator=(Server &&server) noexcept;
    ~Server();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::proto
