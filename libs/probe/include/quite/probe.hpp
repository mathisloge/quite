#pragma once
#include <string>
#include "probe_export.h"

namespace quite
{
struct GrpcServer
{
    //! TODO: add potential secure channels
    std::string server_address;
};

PROBE_EXPORT void setup_hooks(GrpcServer server_config = GrpcServer{.server_address = "unix:///tmp/grpc_probe.sock"});
} // namespace quite
