// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/async_result.hpp>
#include "quite/quite_manager_export.hpp"
namespace quite::manager
{
class QUITE_MANAGER_EXPORT Process
{
  public:
    virtual ~Process() = default;
    virtual bool is_running() = 0;
    virtual int exit_code() = 0;
    virtual AsyncResult<int> async_wait_exit() = 0;
    virtual Result<void> request_exit() = 0;
    virtual Result<void> terminate() = 0;
};
} // namespace quite::manager
