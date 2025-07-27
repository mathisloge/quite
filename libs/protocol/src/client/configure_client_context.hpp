// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/client_rpc.hpp>

namespace quite::proto
{
void configure_client_context(grpc::ClientContext &client_context);
}
