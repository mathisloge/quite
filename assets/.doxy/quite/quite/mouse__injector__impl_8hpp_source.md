

# File mouse\_injector\_impl.hpp

[**File List**](files.md) **>** [**client**](dir_5522d6aca5c3fb454e911c5582f2e576.md) **>** [**mouse\_injector\_impl.hpp**](mouse__injector__impl_8hpp.md)

[Go to the documentation of this file](mouse__injector__impl_8hpp.md)


```C++
#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/injectors/mouse_injector.hpp>
#include "quite/proto/probe.grpc.pb.h"

namespace quite::proto
{
class MouseInjectorImpl final : public core::IMouseInjector
{
  public:
    explicit MouseInjectorImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context,
                               ProbeService::Stub &probe_service_stub);
    AsyncResult<void> single_action(ObjectId target_id, core::MouseAction action) override;

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    ProbeService::Stub &probe_service_stub_;
};
} // namespace quite::proto
```


