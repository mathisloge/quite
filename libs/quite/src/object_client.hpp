#pragma once
#include <expected>
#include <agrpc/grpc_context.hpp>
#include <quite/basic_remote_object.hpp>
#include "quite/errors.hpp"
#include <object/object.grpc.pb.h>
namespace quite
{
class ObjectClient final
{
  public:
    ObjectClient(agrpc::GrpcContext &grpc_context);

    exec::task<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> find_object(
        std::string_view object_name);

  private:
    agrpc::GrpcContext &grpc_context_;
    proto::ObjectService::Stub stub_;
};
} // namespace quite
