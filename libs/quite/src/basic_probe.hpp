#pragma once
#include <quite/manager/process_handle.hpp>
#include "quite/probe.hpp"
namespace quite::client
{
class BasicProbe : public Probe
{
  public:
    explicit BasicProbe(manager::ProcessHandle process);
    manager::Process &process();

    AsyncResult<void> exit() override;

  private:
    manager::ProcessHandle process_;
};
} // namespace quite::client
