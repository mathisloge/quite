

# File qt\_probe\_handler.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**qt\_probe\_handler.hpp**](qt__probe__handler_8hpp.md)

[Go to the documentation of this file](qt__probe__handler_8hpp.md)


```C++
#pragma once
#include <QObject>
#include <quite/async_result.hpp>
#include <quite/proto/probe/probe_handler.hpp>
#include "method_invoker.hpp"

namespace quite::probe
{
AsyncResult<QImage> take_snapshot_of_qobject(QObject *object);

class ObjectTracker;
class QtProbeHandler final : public proto::IProbeHandler
{
  public:
    explicit QtProbeHandler(const ObjectTracker &object_tracker);

    AsyncResult<entt::meta_any> object_instance(ObjectId object_id) override;
    AsyncResult<ImageData> take_snapshot(ObjectId object_id) override;
    AsyncResult<ObjectReference> find_object(ObjectQuery query) override;
    AsyncResult<PropertyMap> fetch_properties(ObjectId object_id, std::vector<std::string> properties) override;
    AsyncResult<void> set_property(ObjectId object_id, std::string property, entt::meta_any value) override;
    AsyncResult<std::vector<ObjectReference>> fetch_windows() override;
    AsyncResult<entt::meta_any> invoke_method(entt::meta_any object,
                                              std::string qualified_method_signature,
                                              std::vector<entt::meta_any> params) override;

  private:
    const ObjectTracker &object_tracker_;
    MethodInvoker method_invoker_;
};
} // namespace quite::probe
```


