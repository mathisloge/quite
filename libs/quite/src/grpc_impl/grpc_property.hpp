#pragma once
#include <quite/property.hpp>
#include "grpc_remote_object.hpp"
namespace quite::grpc_impl
{
class GrpcProperty final : public Property
{
  public:
    explicit GrpcProperty(ProbeServiceHandle probe_service,
                          std::shared_ptr<GrpcRemoteObject> parent,
                          std::string name,
                          const proto::Value &initial_value);
    ~GrpcProperty() override;
    const std::string &name() const noexcept override;
    const Result<Value> &value() const noexcept override;
    AsyncResult<Value> read() noexcept override;
    AsyncResult<Value> write(const Value &value) noexcept override;

  private:
    ProbeServiceHandle probe_service_;
    std::shared_ptr<GrpcRemoteObject> parent_;
    std::string name_;
    Result<Value> last_value_;
};

} // namespace quite::grpc_impl
