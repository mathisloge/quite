#pragma once
#include <quite/async_result.hpp>
#include <quite/value/object_id.hpp>

namespace quite
{
struct ObjectQuery;
}
namespace quite::proto
{
class IObjectHandler
{
  public:
    struct ImageData
    {
        std::uint32_t width;
        std::uint32_t height;
        std::vector<std::uint8_t> image_data;
    };
    virtual ~IObjectHandler() = default;
    virtual AsyncResult<ImageData> take_snapshot(ObjectId object_id) = 0;
    virtual AsyncResult<ObjectReference> find_object(const ObjectQuery &query);
};
} // namespace quite::proto
