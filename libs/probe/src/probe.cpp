#include "quite/probe.hpp"
#include <quite/setup_logger.hpp>
#include "probe_context.hpp"

namespace quite
{
void setup_hooks()
{
    setup_logger();
    std::ignore = probe::ProbeContext::instance(); // create the context.
}
} // namespace quite
