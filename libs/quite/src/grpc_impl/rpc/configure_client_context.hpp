#pragma once
#include <agrpc/client_rpc.hpp>

namespace quite::grpc_impl
{
void configure_client_context(grpc::ClientContext &client_context);
}