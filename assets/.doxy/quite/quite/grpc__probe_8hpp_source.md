

# File grpc\_probe.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**grpc\_impl**](dir_61027e8bdb8101310df75c312f0d65c4.md) **>** [**grpc\_probe.hpp**](grpc__probe_8hpp.md)

[Go to the documentation of this file](grpc__probe_8hpp.md)


```C++
#pragma once
#include <quite/async_result.hpp>
#include <quite/proto/client/client.hpp>
#include <quite/proto/client/probe_client.hpp>
#include "basic_probe.hpp"
#include "grpc_value.hpp"
#include "quite/client/remote_object.hpp"
namespace quite::client
{
class GrpcProbe : public BasicProbe
{
  public:
    explicit GrpcProbe(manager::ProcessHandle process, proto::Client &client, std::string connection_uri);
    AsyncResult<std::shared_ptr<RemoteObject>> find_object(ObjectQuery query) override;
    AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> get_views() override;
    meta::MetaRegistry &meta_registry() override;
    AsyncResult<void> wait_for_started(std::chrono::seconds timeout) override;

  private:
    std::shared_ptr<GrpcValueConverter> value_converter_{std::make_shared<GrpcValueConverter>()};
    std::shared_ptr<proto::ProbeClient> client_;
};
} // namespace quite::client
```


