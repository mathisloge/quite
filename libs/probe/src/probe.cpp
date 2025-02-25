#include "quite/probe.hpp"
#include <entt/locator/locator.hpp>
#include <probe_context.hpp>
#include <quite/setup_logger.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{
void setup_hooks(GrpcServer server_config)
{
    setup_logger(true);
    entt::locator<probe::ProbeContext>::emplace(server_config.server_address);
}
} // namespace quite
