#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/meta/meta_type_id.hpp>
#include <quite/meta/meta_types.hpp>
#include "grpc_remote_object.hpp"
#include "quite/client/property.hpp"

namespace quite::client
{
class GrpcProperty final : public Property
{
  public:
    QUITE_DISABLE_COPY_MOVE(GrpcProperty);
    explicit GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name, entt::meta_any initial_value);
    ~GrpcProperty() override;
    const std::string &name() const override;
    meta::TypeId type_id() const override;
    const Result<entt::meta_any> &value() const override;
    AsyncResult<entt::meta_any> read() override;
    AsyncResult<entt::meta_any> write(entt::meta_any value) override;

  private:
    std::shared_ptr<GrpcRemoteObject> parent_;
    std::string name_;
    meta::TypeId type_id_;
    Result<entt::meta_any> last_value_;
};

} // namespace quite::client
