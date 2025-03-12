#pragma once
#include "quite/manager/process_manager.hpp"
#include "quite/probe.hpp"
namespace quite::client
{
class BasicProbe : public Probe
{
  public:
    explicit BasicProbe(manager::ProcessManager::ProcessHandle process);
    manager::Process &process();

    AsyncResult<void> exit() override;

  private:
    manager::ProcessManager::ProcessHandle process_;
};
} // namespace quite::client
