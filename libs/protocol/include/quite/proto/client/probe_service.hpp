#pragma once
#include <quite/async_result.hpp>
#include <quite/image.hpp>
#include <quite/value/object_id.hpp>
#include <quite/value/object_query.hpp>
#include "quite/quite_protocol_export.hpp"
namespace quite::proto
{
class QUITE_PROTOCOL_EXPORT IProbeService
{
  public:
    virtual ~IProbeService() = default;
    virtual AsyncResult<Image> take_snapshot(ObjectId id) = 0;
    virtual AsyncResult<ObjectReference> find_object(ObjectQuery serach_query) = 0;
    virtual AsyncResult<entt::dense_map<std::string, entt::meta_any>> get_object_properties(
        ObjectId object_id, std::vector<std::string> properties) = 0;
    virtual AsyncResult<std::vector<ObjectReference>> query_top_level_views() = 0;
    virtual AsyncResult<entt::meta_any> invoke_method(ObjectId id,
                                                      std::string method_name,
                                                      std::vector<entt::meta_any> parameters) = 0;
};
} // namespace quite::proto
