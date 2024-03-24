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
void dump_props(QObject *obj)
{
    auto object_meta = quite::ObjectMeta::fromQObject(obj);
    const auto properties = quite::collect_properties(std::move(object_meta));
    spdlog::debug("Object properties: {}", properties);
}

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
    for (auto obj : objects_to_track_)
    {
        dump_props(obj);
        obj->dumpObjectInfo();
        obj->dumpObjectTree();
        if (obj->parent() == nullptr)
        {
            tracked_objects_.emplace(obj);
        }
        //  for outstanding requests do:
        //      if outstanding request matches obj do:
        //          handle_request. RequestHandler should call complete of coroutine.
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
    own_ctx_ = true;
    connect(obj, &QObject::destroyed, this, [this, obj]() {
        std::unique_lock l{locker_};
        objects_to_track_.erase(obj);
    });
    objects_to_track_.emplace(obj);
    startTimer();
    own_ctx_ = false;
}
void ObjectTracker::removeObject(QObject *obj)
{}

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
