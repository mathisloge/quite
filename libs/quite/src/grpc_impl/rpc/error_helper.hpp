#pragma once
#include <grpcpp/support/status.h>
#include <quite/error.hpp>

namespace quite::grpc_impl
{
Error status2error(const grpc::Status &status);
} // namespace quite::grpc_impl
