#pragma once
#include <expected>
#include "error.hpp"

namespace quite
{
template <typename T>
using Result = std::expected<T, Error>;

constexpr auto make_error_result(const ErrorCode code, auto &&message)
{
    return std::unexpected{Error{.code = code, .message = std::forward<decltype(message)>(message)}};
}
} // namespace quite
