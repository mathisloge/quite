#pragma once
#include <agrpc/grpc_context.hpp>
#include "object/object.grpc.pb.h"

namespace quite
{
class ObjectService
{
  public:
    explicit ObjectService(agrpc::GrpcContext &context, grpc::ServerBuilder &builder);
    virtual ~ObjectService();

  protected:
    virtual void onSayHello(const quite::proto::HelloRequest& request, quite::proto::HelloReply& response) = 0;

  private:
    proto::ObjectService::AsyncService service_;
};
} // namespace quite
