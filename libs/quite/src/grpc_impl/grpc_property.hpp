#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/meta/meta_type_id.hpp>
#include <quite/meta/meta_types.hpp>
#include <quite/property.hpp>
#include "grpc_remote_object.hpp"
namespace quite
{
class GrpcProperty final : public Property
{
  public:
    QUITE_DISABLE_COPY_MOVE(GrpcProperty);
    explicit GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name, Value initial_value);
    ~GrpcProperty() override;
    const std::string &name() const override;
    meta::TypeId type_id() const override;
    const Result<Value> &value() const override;
    AsyncResult<Value> read() override;
    AsyncResult<Value> write(const Value &value) override;

  private:
    std::shared_ptr<GrpcRemoteObject> parent_;
    std::string name_;
    meta::TypeId type_id_;
    Result<Value> last_value_;
};

} // namespace quite
