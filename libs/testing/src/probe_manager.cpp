#include "quite/test/probe_manager.hpp"
#include <quite/manager/process_manager.hpp>
#include <quite/probe_manager.hpp>
#include <quite/quite.hpp>
#include <quite/setup_logger.hpp>
#include "quite/test/probe.hpp"

namespace quite::test
{
ProbeManager::ProbeManager()
    : local_{std::make_unique<manager::ProcessManager>(quite::asio_context())}
    , probe_{std::make_unique<client::ProbeManager>()}
{}

ProbeManager::~ProbeManager() = default;

Probe ProbeManager::launch_probe_application(std::string name, const std::string &path_to_application)
{
    auto process = local_->launch_application(std::move(name), path_to_application);
    auto probe_handle = probe_->connect(std::move(process), "...");
    return Probe{std::move(probe_handle)};
}
} // namespace quite::test
