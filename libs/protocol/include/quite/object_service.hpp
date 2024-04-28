#pragma once
#include <agrpc/detail/sender_of.hpp>
#include <agrpc/grpc_context.hpp>
#include "object/object.grpc.pb.h"
#include <asio/awaitable.hpp>

namespace quite
{
class ObjectService
{
  public:
    explicit ObjectService(agrpc::GrpcContext &context, grpc::ServerBuilder &builder);
    virtual ~ObjectService();

  protected:
    virtual void onSayHello(const quite::proto::HelloRequest& request, quite::proto::HelloReply& response) = 0;
    virtual void onFindObject(const quite::proto::ObjectRequest& request, quite::proto::ObjectReply& response) = 0;

  private:
    proto::ObjectService::AsyncService service_;
    agrpc::detail::SenderOf<void()> find_obj_;
};
} // namespace quite
