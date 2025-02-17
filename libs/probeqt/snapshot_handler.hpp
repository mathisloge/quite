#pragma once
#include <QObject>
#include <quite/async_result.hpp>
#include <quite/proto/probe/snapshot_handler.hpp>

namespace quite::probe
{
AsyncResult<QImage> take_snapshot(QObject *object);

class ObjectTracker;
class SnapshotHandler : public proto::ISnapshotHandler
{
  public:
    explicit SnapshotHandler(const ObjectTracker &object_tracker);
    AsyncResult<ImageData> take_snapshot_of_object(ObjectId object_id) override;

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe
