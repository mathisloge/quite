

# File grpc\_manager.cpp

[**File List**](files.md) **>** [**client**](dir_5522d6aca5c3fb454e911c5582f2e576.md) **>** [**grpc\_manager.cpp**](grpc__manager_8cpp.md)

[Go to the documentation of this file](grpc__manager_8cpp.md)


```C++
#include "grpc_manager.hpp"
#include <agrpc/asio_grpc.hpp>
namespace quite::proto
{
GrpcManager::GrpcManager()
    : grpc_context_{std::make_shared<agrpc::GrpcContext>()}
    , grpc_thread_{[grpc_context = grpc_context_]() {
        grpc_context->work_started();
        grpc_context->run();
    }}
{}

GrpcManager::~GrpcManager()
{
    grpc_context_->stop();
};

std::shared_ptr<agrpc::GrpcContext> GrpcManager::context()
{
    return grpc_context_;
}
} // namespace quite::proto
```


