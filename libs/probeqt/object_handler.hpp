#pragma once
#include <QObject>
#include <quite/async_result.hpp>
#include <quite/proto/probe/object_handler.hpp>

namespace quite::probe
{
AsyncResult<QImage> take_snapshot_of_qobject(QObject *object);

class ObjectTracker;
class ObjectHandler : public proto::IObjectHandler
{
  public:
    explicit ObjectHandler(const ObjectTracker &object_tracker);
    AsyncResult<ImageData> take_snapshot(ObjectId object_id) override;

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe
