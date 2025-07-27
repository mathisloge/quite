// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <grpcpp/support/status.h>
#include <quite/error.hpp>

namespace quite::proto
{
grpc::Status result2grpc_status(const Error &error);
Error grpc_status2result(const grpc::Status &error);
} // namespace quite::proto
