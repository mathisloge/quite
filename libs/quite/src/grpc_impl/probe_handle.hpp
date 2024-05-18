#pragma once
#include <quite/proto/probe.grpc.pb.h>
namespace quite::grpc_impl {
    class ProbeClient;
    using ProbeServiceHandle = std::shared_ptr<ProbeClient>;
}
