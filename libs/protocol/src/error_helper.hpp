#pragma once
#include <grpcpp/support/status.h>
#include <quite/error.hpp>

namespace quite::proto
{
grpc::Status result2grpc_status(const Error &error);
} // namespace quite::proto
