#pragma once
#include "object/object.grpc.pb.h"

namespace quite::proto
{
class ObjectServer final
{
  public:
    ObjectServer();
    ~ObjectServer();

  private:
    ObjectService::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
};
} // namespace quite::proto
