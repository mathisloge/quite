#pragma once
#include <quite/proto/client/probe_client.hpp>
#include <quite/proto/client/value_converter.hpp>
namespace quite::client
{
class GrpcValueConverter final : public proto::IValueConverter
{
  public:
    void set_client(std::shared_ptr<proto::ProbeClient> client);
    entt::meta_any from(ObjectReference ref) const override;

  private:
    std::shared_ptr<proto::ProbeClient> client_;
};
// quite::Result<quite::Value> convert(const entt::meta_any &value, std::shared_ptr<proto::ProbeClient> client);
} // namespace quite::client
