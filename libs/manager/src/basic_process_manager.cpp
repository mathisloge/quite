// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/manager/basic_process_manager.hpp"
#include "noop_process.hpp"

namespace quite::manager
{
BasicProcessManager::~BasicProcessManager() = default;

ProcessHandle BasicProcessManager::noop_process()
{
    return ProcessHandle{std::make_shared<NoopProcess>()};
}
} // namespace quite::manager
