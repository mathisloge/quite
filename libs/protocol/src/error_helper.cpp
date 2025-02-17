#include "error_helper.hpp"
namespace quite::proto
{
grpc::Status result2grpc_status(const Error &error)
{
    const grpc::StatusCode code = [code = error.code]() {
        switch (code)
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
        return grpc::StatusCode::UNKNOWN;
    }();
    return grpc::Status{code, error.message};
}
} // namespace quite::proto
