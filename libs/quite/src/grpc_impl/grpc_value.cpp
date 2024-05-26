#include "grpc_value.hpp"

namespace quite::grpc_impl
{
GrpcValue::GrpcValue(proto::Value value)
    : value_{std::move(value)}
{}

GrpcValue::Type GrpcValue::value() const
{
    if (value_.has_bool_val())
    {
        return value_.bool_val();
    }
    else if (value_.has_int_val())
    {
        return value_.int_val();
    }
    else if (value_.has_double_val())
    {
        return value_.double_val();
    }
    else if (value_.has_string_val())
    {
        return value_.string_val();
    }
    return {};
}
} // namespace quite::grpc_impl
