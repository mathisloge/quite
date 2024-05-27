#pragma once
#include <quite/property.hpp>
#include "grpc_remote_object.hpp"
namespace quite::grpc_impl
{

class GrpcProperty final : public Property
{
  public:
    explicit GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name);

    AsyncResult<Value> read() override;
    AsyncResult<bool> write(const Value &value) override;

  private:
    std::shared_ptr<GrpcRemoteObject> parent_;
    std::string name_;
};

} // namespace quite::grpc_impl
