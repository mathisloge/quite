#pragma once
#include <QPointingDevice>
#include <quite/proto/common.pb.h>
#include <quite/proto/keyboard.pb.h>
#include <quite/proto/mouse.pb.h>
#include "../object_id.hpp"
#include "../object_tracker.hpp"
#include <QMouseEvent>
namespace quite::probe
{

class MouseInjector final
{
  public:
    explicit MouseInjector(std::shared_ptr<ObjectTracker> object_tracker);
    ~MouseInjector();

    void perform_action(ObjectId target_id,
                        const proto::MouseAction &action,
                        const proto::MouseButton &button,
                        const proto::KeyboardModifierKey &mod_key,
                        const proto::Vector2F &local_target_point);

  private:
    void dispatchMouseEvent(QObject *target,
                            QMouseEvent::Type event,
                            const proto::MouseButton &button,
                            const proto::KeyboardModifierKey &mod_key,
                            const proto::Vector2F &local_target_point);

  private:
    std::shared_ptr<ObjectTracker> object_tracker_;
    QPointingDevice mouse_;
};
} // namespace quite::probe
