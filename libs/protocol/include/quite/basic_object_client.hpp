#pragma once
#include <agrpc/grpc_context.hpp>
#include <asio/awaitable.hpp>
#include "object/object.grpc.pb.h"

namespace quite
{
class BasicObjectClient
{
  public:
    explicit BasicObjectClient(agrpc::GrpcContext &context);
    virtual ~BasicObjectClient();

  protected:
    agrpc::GrpcContext &context_;
    proto::ObjectService::Stub stub_;
};
} // namespace quite
