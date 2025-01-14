#pragma once
#include <grpcpp/support/status.h>
#include <quite/error.hpp>
namespace quite::probe
{
constexpr grpc::StatusCode error_code2grpc_status_code(const ErrorCode error_code)
{
    switch (error_code)
    {
    case ErrorCode::unknown:
        return grpc::StatusCode::UNKNOWN;
    case ErrorCode::cancelled:
        return grpc::StatusCode::CANCELLED;
    case ErrorCode::invalid_argument:
        return grpc::StatusCode::INVALID_ARGUMENT;
    case ErrorCode::deadline_exceeded:
        return grpc::StatusCode::DEADLINE_EXCEEDED;
    case ErrorCode::not_found:
        return grpc::StatusCode::NOT_FOUND;
    case ErrorCode::failed_precondition:
        return grpc::StatusCode::FAILED_PRECONDITION;
    case ErrorCode::aborted:
        return grpc::StatusCode::ABORTED;
    case ErrorCode::unimplemented:
        return grpc::StatusCode::UNIMPLEMENTED;
    case ErrorCode::unavailable:
        return grpc::StatusCode::UNAVAILABLE;
    }
}

constexpr grpc::Status error2grpc_status(const Error &error)
{
    return grpc::Status{error_code2grpc_status_code(error.code), error.message};
}
} // namespace quite::probe
