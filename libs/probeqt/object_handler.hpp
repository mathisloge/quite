#pragma once
#include <QObject>
#include <quite/async_result.hpp>
#include <quite/proto/probe/object_handler.hpp>
#include "method_invoker.hpp"

namespace quite::probe
{
AsyncResult<QImage> take_snapshot_of_qobject(QObject *object);

class ObjectTracker;
class ObjectHandler final : public proto::IObjectHandler
{
  public:
    explicit ObjectHandler(const ObjectTracker &object_tracker);

    AsyncResult<entt::meta_any> object_instance(ObjectId object_id) override;
    AsyncResult<ImageData> take_snapshot(ObjectId object_id) override;
    AsyncResult<ObjectReference> find_object(ObjectQuery query) override;
    AsyncResult<PropertyMap> fetch_properties(ObjectId object_id) override;
    AsyncResult<std::vector<ObjectReference>> fetch_windows() override;
    AsyncResult<entt::meta_any> invoke_method(const entt::meta_any &object,
                                              std::string_view qualified_method_signature,
                                              std::span<entt::meta_any> params) override;

  private:
    const ObjectTracker &object_tracker_;
    MethodInvoker method_invoker_;
};
} // namespace quite::probe
