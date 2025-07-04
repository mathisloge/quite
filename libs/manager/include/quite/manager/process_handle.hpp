#pragma once
#include <memory>
#include "quite/quite_manager_export.hpp"

namespace quite::manager
{
class Process;
class QUITE_MANAGER_EXPORT ProcessHandle
{
  public:
    explicit ProcessHandle(std::shared_ptr<Process> process);
    Process &instance();
    Process *operator->();

  private:
    std::shared_ptr<Process> process_;
};
} // namespace quite::manager
