#pragma once
#include <string>
#include "quite/quite_probe_export.hpp"

namespace quite
{
struct GrpcServer
{
    //! TODO: add potential secure channels
    std::string server_address;
};

PROBE_EXPORT void setup_hooks(GrpcServer server_config = GrpcServer{.server_address = "unix:///tmp/grpc_probe.sock"});
} // namespace quite
