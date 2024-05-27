#pragma once
#include <expected>
#include "errors.hpp"

namespace quite
{
template <typename T>
using Result = std::expected<T, Error>;
}
