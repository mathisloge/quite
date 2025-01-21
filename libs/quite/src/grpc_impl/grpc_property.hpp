#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/meta/meta_type_id.hpp>
#include <quite/meta/meta_types.hpp>
#include <quite/property.hpp>
#include "grpc_remote_object.hpp"
namespace quite::grpc_impl
{
class GrpcProperty final : public Property
{
  public:
    QUITE_DISABLE_COPY_MOVE(GrpcProperty);
    explicit GrpcProperty(ProbeServiceHandle probe_service,
                          std::shared_ptr<GrpcRemoteObject> parent,
                          std::string name,
                          const proto::Value &initial_value);
    ~GrpcProperty() override;
    const std::string &name() const override;
    meta::TypeId type_id() const override;
    const Result<Value> &value() const override;
    AsyncResult<Value> read() override;
    AsyncResult<Value> write(const Value &value) override;

  private:
    ProbeServiceHandle probe_service_;
    std::shared_ptr<GrpcRemoteObject> parent_;
    std::string name_;
    meta::TypeId type_id_;
    Result<Value> last_value_;
};

} // namespace quite::grpc_impl
