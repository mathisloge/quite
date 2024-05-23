#pragma once
#include <expected>
#include <string>
namespace quite
{

enum class ErrorCode
{
    unknown,          //!< Just as the zero enum. Shouldn't be emitted.
    cancelled,        //!< The operation was cancelled
    invalid_argument, //!< indicates arguments that are problematic regardless of the state of the system (e.g., a
    //!< malformed file name
    deadline_exceeded,   //!< Deadline expired before operation could complete
    not_found,           //!< Some requested entity (e.g., file or directory) was not found.
    failed_precondition, //!< Operation was rejected because the system is not in a state required for the operation's
    //!< execution
    aborted,       //!< The operation was aborted
    unimplemented, //!< Operation is not implemented or not supported/enabled in this service.
    unavailable,   //!< The called operation endpoint might not be ready yet.
};

struct Error
{
    ErrorCode code;
    std::string message;
};

template <typename T>
using Result = std::expected<T, Error>;
} // namespace quite
