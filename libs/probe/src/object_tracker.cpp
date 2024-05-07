#include "object_tracker.hpp"
#include <QDebug>
#include <QMetaProperty>
#include <QThread>
#include <QVariant>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <fmt/ranges.h>
#include <private/qv4executablecompilationunit_p.h>
#include <qcoreapplication.h>
#include <qevent.h>
#include <spdlog/spdlog.h>
#include "property_collector.hpp"
#include <spdlog/sinks/qt_sinks.h>

namespace
{
void dump_props(QObject *obj)
{
    // obj->dumpObjectInfo();
    // obj->dumpObjectTree();
    auto object_meta = quite::ObjectMeta::fromQObject(obj);
    const auto properties = quite::collect_properties(std::move(object_meta));
}

} // namespace
namespace quite
{

ObjectTracker::ObjectTracker()
    : test_mouse_{QStringLiteral("TestingMouse"),
                  100,
                  QInputDevice::DeviceType::Mouse,
                  QPointingDevice::PointerType::Generic,
                  QInputDevice::Capability::MouseEmulation,
                  1,
                  2}
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
        //dump_props(obj);
        // if (obj->parent() == nullptr)
        {
            if(obj->objectName() == "logArea") {
                spdlog::error("XXXX GOT LOGAREA");
                //spdlog::default_logger()->sinks().emplace_back(std::make_shared<spdlog::sinks::qt_sink_st>(obj, "setText"));
            }
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
    connect(obj, &QObject::destroyed, this, [this, obj]() { removeObject((obj)); });
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

std::expected<ObjectInfo, ObjectErrC> ObjectTracker::findObject(const std::string &object_name)
{
    std::shared_lock l{locker_};
    own_ctx_ = true;
    for (auto &&obj : tracked_objects_)
    {
        // auto properties = quite::collect_properties(object_meta);
        if (obj->objectName() == QString::fromStdString(object_name))
        {
            auto object_meta = quite::ObjectMeta::fromQObject(obj);
            own_ctx_ = false;
            return ObjectInfo{
                .object_id = reinterpret_cast<std::uintptr_t>(obj),
                .class_type = object_meta.meta_object->className(),
            };
        }
    }
    own_ctx_ = false;
    return std::unexpected(ObjectErrC::not_found);
}

std::expected<std::string, ObjectErrC> ObjectTracker::get_property(QObject *obj, const std::string &property_name)
{
    std::shared_lock l{locker_};
    own_ctx_ = true;
    auto it = tracked_objects_.find(obj);
    if (it != tracked_objects_.end())
    {
        auto prop = obj->property(property_name.c_str()).toString().toStdString();
        own_ctx_ = false;
        return prop;
    }
    own_ctx_ = false;
    return std::unexpected(ObjectErrC::not_found);
}

void ObjectTracker::mouse_click(QObject *obj)
{
    std::shared_lock l{locker_};
    own_ctx_ = true;
    auto it = tracked_objects_.find(obj);
    if (it != tracked_objects_.end())
    {
        spdlog::debug("click!");
        auto ev = new QMouseEvent(QMouseEvent::Type::MouseButtonPress,
                                  QPointF{0, 0},QPointF{0, 0},
                                  Qt::MouseButton::LeftButton,
                                  Qt::MouseButton::LeftButton,
                                  {},&test_mouse_);
        spdlog::debug("click2!");
        QCoreApplication::postEvent(obj, ev);
        spdlog::debug("click3! {}-{}", obj->property("x").toInt(), obj->property("y").toInt());
        QTimer::singleShot(std::chrono::seconds{1}, [this,obj]() {
            auto ev = new QMouseEvent(QMouseEvent::Type::MouseButtonRelease,
                                      QPointF{0, 0}, QPointF{0, 0},
                                      Qt::MouseButton::LeftButton,
                                      Qt::MouseButton::LeftButton,
                                      {}, &test_mouse_);
            QCoreApplication::postEvent(obj, ev);
        });
    }
    own_ctx_ = false;
}

void ObjectTracker::removeObject(QObject *obj)
{
    std::unique_lock l{locker_};
    own_ctx_ = true;
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
