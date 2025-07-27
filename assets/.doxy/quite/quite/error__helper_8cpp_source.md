

# File error\_helper.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**error\_helper.cpp**](error__helper_8cpp.md)

[Go to the documentation of this file](error__helper_8cpp.md)


```C++
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

Error grpc_status2result(const grpc::Status &error)
{
    const ErrorCode code = [code = error.error_code()]() {
        switch (code)
        {
        case grpc::CANCELLED:
            return ErrorCode::cancelled;
        case grpc::INVALID_ARGUMENT:
            return ErrorCode::invalid_argument;
        case grpc::DEADLINE_EXCEEDED:
            return ErrorCode::deadline_exceeded;
        case grpc::NOT_FOUND:
        case grpc::RESOURCE_EXHAUSTED:
            return ErrorCode::not_found;
        case grpc::ALREADY_EXISTS:
        case grpc::PERMISSION_DENIED:
        case grpc::FAILED_PRECONDITION:
        case grpc::OUT_OF_RANGE:
            return ErrorCode::failed_precondition;
        case grpc::UNAUTHENTICATED:
        case grpc::ABORTED:
            return ErrorCode::aborted;
        case grpc::UNIMPLEMENTED:
            return ErrorCode::unimplemented;
        case grpc::UNAVAILABLE:
            return ErrorCode::unavailable;
        case grpc::OK:
        case grpc::DATA_LOSS:
        case grpc::UNKNOWN:
        case grpc::INTERNAL:
        case grpc::DO_NOT_USE:
            return ErrorCode::unknown;
        }
        return ErrorCode::unknown;
    }();

    return Error{
        .code = code,
        .message = error.error_message(),
    };
}
} // namespace quite::proto
```


