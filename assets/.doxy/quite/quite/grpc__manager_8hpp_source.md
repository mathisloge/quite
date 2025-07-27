

# File grpc\_manager.hpp

[**File List**](files.md) **>** [**client**](dir_5522d6aca5c3fb454e911c5582f2e576.md) **>** [**grpc\_manager.hpp**](grpc__manager_8hpp.md)

[Go to the documentation of this file](grpc__manager_8hpp.md)


```C++
#pragma once
#include <memory>
#include <thread>
#include <agrpc/grpc_context.hpp>
#include <quite/disable_copy_move.hpp>

namespace quite::proto
{
class GrpcManager final
{
  public:
    QUITE_DISABLE_COPY_MOVE(GrpcManager);
    GrpcManager();
    ~GrpcManager();

    std::shared_ptr<agrpc::GrpcContext> context();

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    std::jthread grpc_thread_;
};
} // namespace quite::proto
```


