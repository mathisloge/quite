#include "object_tracker.hpp"
#include <QDebug>
#include <QMetaProperty>
#include <QThread>
#include <QVariant>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <entt/meta/factory.hpp>
#include <fmt/ranges.h>
#include <private/qv4executablecompilationunit_p.h>
#include <quite/logger.hpp>
#include "property_collector.hpp"
#include "proto_converters.hpp"

DEFINE_LOGGER(object_tracker_logger)

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
namespace quite::probe
{

ObjectTracker::ObjectTracker()
{
    init_timer_.setInterval(0);
    init_timer_.setSingleShot(true);
    connect(&init_timer_, &QTimer::timeout, this, &ObjectTracker::process_new_objects);
}
ObjectTracker::~ObjectTracker() = default;

void ObjectTracker::process_new_objects()
{
    std::unique_lock l{locker_};
    for (auto &&obj : objects_to_track_)
    {
        // dump_props(obj);
        if (obj->parent() == nullptr and obj->isWindowType())
        {
            top_level_views_.emplace(obj);
        }
        tracked_objects_.emplace(obj);
    }
    objects_to_track_.clear();
}

void ObjectTracker::add_object(QObject *obj)
{
    if (own_ctx_)
    {
        return;
    }
    std::unique_lock l{locker_};
    InOwnContext c{own_ctx_};
    connect(obj, &QObject::destroyed, this, [this, obj]() { remove_object((obj)); });
    objects_to_track_.emplace(obj);
    start_timer();
}

void ObjectTracker::begin_context()
{
    own_ctx_ = true;
}

void ObjectTracker::end_context()
{
    own_ctx_ = false;
}

const std::unordered_set<QObject *> &ObjectTracker::top_level_views() const
{
    return top_level_views_;
}

std::expected<ObjectInfo, ObjectErrC> ObjectTracker::find_object(const std::string &object_name) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    for (auto &&obj : tracked_objects_)
    {
        if (obj->objectName() == QString::fromStdString(object_name))
        {
            auto object_meta = quite::ObjectMeta::from_qobject(obj);
            return ObjectInfo{
                .object_id = reinterpret_cast<std::uintptr_t>(obj),
                .class_type = static_cast<meta::TypeId>(object_meta.meta_object->metaType().id()),
            };
        }
    }
    return std::unexpected(ObjectErrC::not_found);
}

namespace
{
bool operator==(const QVariant &variant, const proto::Value &value)
{
    auto custom_meta_type = entt::resolve(entt::hashed_string{variant.metaType().name()}.value());
    if (not custom_meta_type)
    {
        return false;
    }
    const auto any_obj = custom_meta_type.from_void(variant.data());
    const auto value_meta = probe::meta_from_value(value);

    const entt::meta_any casted_value = any_obj.allow_cast(value_meta.type());
    return casted_value == value_meta;
}

bool match_property(QObject *object, std::string_view property_name, const proto::Value &value)
{
    const auto property_value = object->property(property_name.data());
    return property_value.isValid() and property_value == value;
}
} // namespace

std::expected<ObjectInfo, ObjectErrC> ObjectTracker::find_object_by_query(const proto::ObjectSearchQuery &query) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};

    for (auto &&obj : tracked_objects_)
    {
        bool property_matches = true;
        for (auto &&[prop_name, prop_value] : query.properties())
        {
            if (not match_property(obj, prop_name, prop_value))
            {
                property_matches = false;
                break;
            }
        }

        if (property_matches)
        {
            return ObjectInfo{
                .object_id = reinterpret_cast<std::uintptr_t>(obj),
                .class_type = static_cast<meta::TypeId>(obj->metaObject()->metaType().id()),
            };
        }
    }

    return std::unexpected(ObjectErrC::not_found);
}

std::expected<QObject *, ObjectErrC> ObjectTracker::get_object_by_id(probe::ObjectId obj_id) const
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
                                                                   const std::string &property_name) const
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

void ObjectTracker::remove_object(QObject *obj)
{
    std::unique_lock l{locker_};
    InOwnContext c{own_ctx_};
    if (const auto it = objects_to_track_.find(obj); it != objects_to_track_.end())
    {
        LOG_TRACE_L1(object_tracker_logger(), "remove obj from objects_to_track {}", obj->objectName().toStdString());
        objects_to_track_.erase(it);
    }
    else if (const auto it = tracked_objects_.find(obj); it != tracked_objects_.end())
    {
        LOG_TRACE_L1(object_tracker_logger(), "remove obj from tracked_objects {}", obj->objectName().toStdString());
        tracked_objects_.erase(it);
    }
    if (const auto it = top_level_views_.find(obj); it != top_level_views_.end())
    {
        top_level_views_.erase(it);
    }
}

void ObjectTracker::start_timer()
{
    static const auto kStartFncIdx = QTimer::staticMetaObject.indexOfMethod("start()");
    Q_ASSERT(kStartFncIdx >= 0);

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
        m = QTimer::staticMetaObject.method(kStartFncIdx);
        Q_ASSERT(m.methodIndex() >= 0);
    }
    m.invoke(&init_timer_, Qt::QueuedConnection);
    //}
}
} // namespace quite::probe
