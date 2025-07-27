#include "quite/client/probe_manager.hpp"
#include "context.hpp"
#include "grpc_impl/grpc_probe.hpp"

namespace quite::client
{
struct ProbeManager::Impl
{};

ProbeManager::ProbeManager()
    : impl_{std::make_unique<Impl>()}
{}

ProbeManager::~ProbeManager()
{}

ProbeHandle ProbeManager::connect(manager::ProcessHandle handle, const std::string &connection_url)
{
    return ProbeHandle{std::make_shared<GrpcProbe>(
        std::move(handle), quite::Context::Instance().backend_client(), std::move(connection_url))};
}
} // namespace quite::client
