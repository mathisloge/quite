#pragma once
#include <agrpc/client_rpc.hpp>

namespace quite::proto
{
void configure_client_context(grpc::ClientContext &client_context);
}
