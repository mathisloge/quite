// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <exec/task.hpp>
#include "result.hpp"

namespace quite
{
template <typename T>
using AsyncResult = exec::task<Result<T>>;
}
