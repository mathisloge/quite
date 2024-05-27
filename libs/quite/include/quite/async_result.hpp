#pragma once
#include <exec/task.hpp>
#include "result.hpp"

namespace quite
{
template <typename T>
using AsyncResult = exec::task<Result<T>>;
}
