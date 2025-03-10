#pragma once
#include "quite/manager/application_manager.hpp"
#include "quite/probe.hpp"
namespace quite::client
{
class BasicProbe : public Probe
{
  public:
    explicit BasicProbe(manager::ApplicationManager::ApplicationHandle process);
    manager::Application &process();

    AsyncResult<void> exit() override;

  private:
    manager::ApplicationManager::ApplicationHandle process_;
};
} // namespace quite::client
