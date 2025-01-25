#include "quite/probe.hpp"
#include <entt/locator/locator.hpp>
#include <probe_context.hpp>
#include <quite/setup_logger.hpp>

namespace quite
{
void setup_hooks(GrpcServer server_config)
{
    setup_logger(true);
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_config.server_address, grpc::InsecureServerCredentials());
    entt::locator<probe::ProbeContext>::emplace(builder);
}
} // namespace quite
