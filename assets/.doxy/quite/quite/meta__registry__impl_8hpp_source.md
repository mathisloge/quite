

# File meta\_registry\_impl.hpp

[**File List**](files.md) **>** [**client**](dir_5522d6aca5c3fb454e911c5582f2e576.md) **>** [**meta\_registry\_impl.hpp**](meta__registry__impl_8hpp.md)

[Go to the documentation of this file](meta__registry__impl_8hpp.md)


```C++
#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/meta/meta_registry.hpp>
#include "quite/proto/meta_service.grpc.pb.h"

namespace quite::proto
{
class MetaRegistryImpl : public meta::MetaRegistry
{
  public:
    explicit MetaRegistryImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context, MetaService::Stub &meta_service_stub);
    AsyncResult<meta::Type> lookup_type(meta::TypeId type_id) override;

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    MetaService::Stub &meta_service_stub_;
};
} // namespace quite::proto
```


