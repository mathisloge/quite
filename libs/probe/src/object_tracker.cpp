#include "object_tracker.hpp"
#include <QDebug>
#include <QMetaProperty>
#include <QThread>
#include <QVariant>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <fmt/ranges.h>
#include <private/qv4executablecompilationunit_p.h>
#include <spdlog/spdlog.h>
#include "property_collector.hpp"

namespace
{
class InOwnContext final
{
  public:
    InOwnContext(std::atomic_bool &context)
        : context_{context}
    {
        context_ = true;
    }
    ~InOwnContext()
    {
        context_ = false;
    }

  private:
    std::atomic_bool &context_;
};

} // namespace
namespace quite
{

ObjectTracker::ObjectTracker()
{
    init_timer_.setInterval(0);
    init_timer_.setSingleShot(true);
    connect(&init_timer_, &QTimer::timeout, this, &ObjectTracker::processNewObjects);
}
ObjectTracker::~ObjectTracker() = default;

void ObjectTracker::processNewObjects()
{
    std::unique_lock l{locker_};
    for (auto obj : objects_to_track_)
    {
        // dump_props(obj);
        if (obj->parent() == nullptr and obj->isWindowType())
        {
            obj->dumpObjectInfo();
            top_level_views_.emplace(obj);
        }
        tracked_objects_.emplace(obj);
    }
    objects_to_track_.clear();
}

void ObjectTracker::addObject(QObject *obj)
{
    if (own_ctx_)
    {
        return;
    }
    std::unique_lock l{locker_};
    InOwnContext c{own_ctx_};
    connect(obj, &QObject::destroyed, this, [this, obj]() { removeObject((obj)); });
    objects_to_track_.emplace(obj);
    startTimer();
}

void ObjectTracker::beginContext()
{
    own_ctx_ = true;
}

void ObjectTracker::endContext()
{
    own_ctx_ = false;
}

const std::unordered_set<QObject *> &ObjectTracker::top_level_views() const
{
    return top_level_views_;
}

std::expected<ObjectInfo, ObjectErrC> ObjectTracker::findObject(const std::string &object_name)
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    for (auto &&obj : tracked_objects_)
    {
        // auto properties = quite::collect_properties(object_meta);
        if (obj->objectName() == QString::fromStdString(object_name))
        {
            auto object_meta = quite::ObjectMeta::from_qobject(obj);
            return ObjectInfo{
                .object_id = reinterpret_cast<std::uintptr_t>(obj),
                .class_type = object_meta.meta_object->className(),
            };
        }
    }
    return std::unexpected(ObjectErrC::not_found);
}

std::expected<QObject *, ObjectErrC> ObjectTracker::get_object_by_id(probe::ObjectId obj_id)
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    auto it = tracked_objects_.find(reinterpret_cast<QObject *>(obj_id));
    if (it != tracked_objects_.end())
    {
        return *it;
    }
    return std::unexpected(ObjectErrC::not_found);
}

std::expected<std::string, ObjectErrC> ObjectTracker::get_property(probe::ObjectId obj_id,
                                                                   const std::string &property_name)
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    auto it = tracked_objects_.find(reinterpret_cast<QObject *>(obj_id));
    if (it != tracked_objects_.end())
    {
        return (*it)->property(property_name.c_str()).toString().toStdString();
    }
    return std::unexpected(ObjectErrC::not_found);
}

void ObjectTracker::removeObject(QObject *obj)
{
    std::unique_lock l{locker_};
    InOwnContext c{own_ctx_};
    if (const auto it = objects_to_track_.find(obj); it != objects_to_track_.end())
    {
        spdlog::trace("remove obj from objects_to_track {}", obj->objectName().toStdString());
        objects_to_track_.erase(it);
    }
    else if (const auto it = tracked_objects_.find(obj); it != tracked_objects_.end())
    {
        spdlog::trace("remove obj from tracked_objects {}", obj->objectName().toStdString());
        tracked_objects_.erase(it);
    }
    if (const auto it = top_level_views_.find(obj); it != top_level_views_.end())
    {
        top_level_views_.erase(it);
    }
}

void ObjectTracker::startTimer()
{
    if (init_timer_.isActive())
    {
        return;
    }
    // if (thread() == QThread::currentThread())
    //{
    //     init_timer_.start();
    // }
    // else
    //{
    static QMetaMethod m;
    if (m.methodIndex() < 0)
    {
        const auto idx = QTimer::staticMetaObject.indexOfMethod("start()");
        Q_ASSERT(idx >= 0);
        m = QTimer::staticMetaObject.method(idx);
        Q_ASSERT(m.methodIndex() >= 0);
    }
    m.invoke(&init_timer_, Qt::QueuedConnection);
    //}
}
} // namespace quite
