#pragma once
#include <expected>
#include "error.hpp"

namespace quite
{
template <typename T>
using Result = std::expected<T, Error>;

template <typename T>
constexpr Result<T> make_error_result(const ErrorCode code, std::string message)
{
    return std::unexpected{Error{.code = code, .message = std::forward<std::string>(message)}};
}
} // namespace quite
