#pragma once
#include "quite/manager/process.hpp"

namespace quite::manager
{
class NoopProcess final : public Process
{
  public:
    bool is_running() override;
    int exit_code() override;
    AsyncResult<int> async_wait_exit() override;
    Result<void> request_exit() override;
    Result<void> terminate() override;
};
} // namespace quite::manager
