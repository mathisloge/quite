

# File probe\_manager.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**probe\_manager.cpp**](client_2src_2probe__manager_8cpp.md)

[Go to the documentation of this file](client_2src_2probe__manager_8cpp.md)


```C++
#include "quite/client/probe_manager.hpp"
#include "context.hpp"
#include "grpc_impl/grpc_probe.hpp"

namespace quite::client
{
struct ProbeManager::Impl
{};

ProbeManager::ProbeManager()
    : impl_{std::make_unique<Impl>()}
{}

ProbeManager::~ProbeManager()
{}

ProbeHandle ProbeManager::connect(manager::ProcessHandle handle, const std::string &connection_url)
{
    return ProbeHandle{std::make_shared<GrpcProbe>(
        std::move(handle), quite::Context::Instance().backend_client(), std::move(connection_url))};
}
} // namespace quite::client
```


