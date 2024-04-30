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
    obj->dumpObjectInfo();
    obj->dumpObjectTree();
    auto object_meta = quite::ObjectMeta::fromQObject(obj);
    const auto properties = quite::collect_properties(std::move(object_meta));
    spdlog::debug("Object properties of {}: {}", object_meta.meta_object->className(), properties);
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
    std::unique_lock l{locker_};
    for (auto obj : objects_to_track_)
    {
        // dump_props(obj);
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

void ObjectTracker::beginContext()
{
    own_ctx_ = true;
}

void ObjectTracker::endContext()
{
    own_ctx_ = false;
}

namespace
{
QObject *find_object(const std::string &object_name)
{
    return nullptr;
}
} // namespace

std::unordered_map<std::string, std::string> ObjectTracker::findObject(const std::string &object_name)
{
    std::shared_lock l{locker_};
    own_ctx_ = true;
    for (auto &&obj : tracked_objects_)
    {
        auto object_meta = quite::ObjectMeta::fromQObject(obj);
        const auto properties = quite::collect_properties(object_meta);
        if (const auto it = properties.find("objectName"); it != properties.end())
        {
            spdlog::debug("got {} searched for {}", it->second, object_name);   
            if (it->second == object_name)
            {
                spdlog::debug("return {}", object_meta.meta_object->className());
                own_ctx_ = false;
                return properties;
            }
        }
    }
    own_ctx_ = false;
    return {};
}

void ObjectTracker::removeObject(QObject *obj)
{
    std::unique_lock l{locker_};
    own_ctx_ = true;
    if (const auto it = objects_to_track_.find(obj); it != objects_to_track_.end())
    {
        spdlog::debug("remove obj from objects_to_track");
        objects_to_track_.erase(it);
    }
    else if (const auto it = tracked_objects_.find(obj); it != tracked_objects_.end())
    {
        spdlog::debug("remove obj from tracked_objects");
        tracked_objects_.erase(it);
    }
    own_ctx_ = false;
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
