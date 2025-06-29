#pragma once
#include <entt/container/dense_map.hpp>
#include <entt/meta/meta.hpp>
#include <quite/async_result.hpp>
#include <quite/value/object_id.hpp>
#include "quite/quite_protocol_export.hpp"

namespace quite
{
struct ObjectQuery;
}
namespace quite::proto
{
class QUITE_PROTOCOL_EXPORT IProbeHandler
{
  public:
    struct ImageData
    {
        std::uint32_t width;
        std::uint32_t height;
        std::vector<std::uint8_t> image_data;
    };
    using PropertyMap = entt::dense_map<std::string, entt::meta_any>;

    virtual ~IProbeHandler() = default;
    virtual AsyncResult<entt::meta_any> object_instance(ObjectId object_id) = 0;
    virtual AsyncResult<ImageData> take_snapshot(ObjectId object_id) = 0;
    virtual AsyncResult<ObjectReference> find_object(ObjectQuery query) = 0;
    virtual AsyncResult<PropertyMap> fetch_properties(ObjectId object_id, std::vector<std::string> properties) = 0;
    virtual AsyncResult<std::vector<ObjectReference>> fetch_windows() = 0;
    virtual AsyncResult<entt::meta_any> invoke_method(entt::meta_any object,
                                                      std::string qualified_method_signature,
                                                      std::vector<entt::meta_any> params) = 0;
};
} // namespace quite::proto
