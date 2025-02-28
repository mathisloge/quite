#pragma once
#include <agrpc/grpc_context.hpp>
#include "quite/proto/client/probe_service.hpp"
#include "quite/proto/probe.grpc.pb.h"

namespace quite::proto
{
class ProbeServiceImpl final : public IProbeService
{
  public:
    explicit ProbeServiceImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context, ProbeService::Stub &probe_service_stub);

    AsyncResult<Image> take_snapshot(ObjectId id) override;
    AsyncResult<ObjectReference> find_object(ObjectQuery serach_query) override;
    AsyncResult<entt::dense_map<std::string, entt::meta_any>> get_object_properties(
        ObjectId object_id, std::vector<std::string> properties) override;
    AsyncResult<std::vector<ObjectReference>> query_top_level_views() override;
    AsyncResult<entt::meta_any> invoke_method(ObjectId id,
                                              std::string method_name,
                                              std::vector<entt::meta_any> parameters) override;

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    ProbeService::Stub &probe_service_stub_;
};
} // namespace quite::proto
