#pragma once
#include <expected>
#include <agrpc/grpc_context.hpp>
#include <object/object.grpc.pb.h>
#include <quite/basic_remote_object.hpp>
#include "quite/errors.hpp"
namespace quite
{
class ObjectClient final : public std::enable_shared_from_this<ObjectClient>
{
  public:
    ObjectClient(agrpc::GrpcContext &grpc_context);

    exec::task<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> find_object(
        std::string_view object_name);

    agrpc::GrpcContext &context()
    {
        return grpc_context_;
    }
    
    proto::ObjectService::Stub &stub()
    {
        return stub_;
    }

  private:
    agrpc::GrpcContext &grpc_context_;
    proto::ObjectService::Stub stub_;
};
} // namespace quite
