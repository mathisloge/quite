// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <boost/process/v2/process.hpp>
#include "quite/manager/process.hpp"

namespace quite::manager
{
class ProcessImpl final : public Process
{
  public:
    explicit ProcessImpl(boost::process::v2::process &&process);
    bool is_running() override;
    int exit_code() override;
    AsyncResult<int> async_wait_exit() override;
    Result<void> request_exit() override;
    Result<void> terminate() override;

  private:
    boost::process::v2::process process_;
};
} // namespace quite::manager
