#pragma once
#include <expected>
#include "error.hpp"

namespace quite
{
template <typename T>
using Result = std::expected<T, Error>;
}
