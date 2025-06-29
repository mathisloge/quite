#pragma once
#include <expected>
#include "error.hpp"

namespace quite
{

/**
 * @brief Alias for a result type that holds either a value of type T or an Error.
 *
 * This is a convenience alias for std::expected<T, Error>, used to represent
 * the result of an operation that may fail with a quite::Error.
 *
 * @tparam T The type of the expected value on success.
 */
template <typename T>
using Result = std::expected<T, Error>;

/**
 * @brief Helper function to create an error result.
 *
 * Constructs a std::unexpected containing a quite::Error with the given code and message.
 *
 * @tparam MessageT The type of the error message (deduced).
 * @param code The error code.
 * @param message The error message.
 * @return std::unexpected<Error> containing the error.
 */
template <typename MessageT>
constexpr auto make_error_result(const ErrorCode code, MessageT &&message)
{
    return std::unexpected{Error{.code = code, .message = std::forward<MessageT>(message)}};
}

} // namespace quite
