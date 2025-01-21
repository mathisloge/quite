#include "quite/probe.hpp"
#include <entt/locator/locator.hpp>
#include <probe_context.hpp>
#include <quite/setup_logger.hpp>

namespace quite
{
void setup_hooks()
{
    setup_logger(true);
    entt::locator<probe::ProbeContext>::emplace();
}
} // namespace quite
