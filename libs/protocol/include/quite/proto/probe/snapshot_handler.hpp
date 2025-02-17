#pragma once
#include <quite/async_result.hpp>
#include <quite/value/object_id.hpp>

namespace quite::proto
{
class ISnapshotHandler
{
  public:
    struct ImageData
    {
        std::uint32_t width;
        std::uint32_t height;
        std::vector<std::uint8_t> image_data;
    };
    virtual ~ISnapshotHandler() = default;
    virtual AsyncResult<ImageData> take_snapshot_of_object(ObjectId object_id) = 0;
};
} // namespace quite::proto
