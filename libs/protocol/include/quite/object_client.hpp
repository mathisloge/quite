#pragma once
#include <agrpc/grpc_context.hpp>
#include <asio/awaitable.hpp>
#include "object/object.grpc.pb.h"

namespace quite
{
class ObjectClient final
{
  public:
    explicit ObjectClient(agrpc::GrpcContext& context);
    ~ObjectClient();

    asio::awaitable<std::string> sayHello(const std::string &name);

  private:
    agrpc::GrpcContext& context_;
    proto::ObjectService::Stub stub_;
};
} // namespace quite
