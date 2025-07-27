// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <exec/task.hpp>
#include <stdexec/execution.hpp>

#define ASYNC_BLOCK stdexec::sync_wait([&]() -> exec::task<void> {

#define ASYNC_BLOCK_END                                                                                                \
    co_return;                                                                                                         \
    }());
