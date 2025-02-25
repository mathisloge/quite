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
#include "qt_meta_type_accessor.hpp"

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

Result<ObjectReference> ObjectTracker::find_object(const std::string &object_name) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    for (auto &&obj : tracked_objects_)
    {
        if (obj->objectName() == QString::fromStdString(object_name))
        {
            return ObjectReference{
                .object_id = reinterpret_cast<std::uintptr_t>(obj),
                .type_id = static_cast<meta::TypeId>(try_get_qt_meta_type(obj).id()),
            };
        }
    }
    return make_error_result<ObjectReference>(ErrorCode::not_found,
                                              fmt::format("Could not found object with name {}", object_name));
}

namespace
{
bool operator==(const QVariant &variant, const entt::meta_any &value)
{
    auto custom_meta_type = entt::resolve(entt::hashed_string{variant.metaType().name()}.value());
    if (not custom_meta_type)
    {
        return false;
    }
    const auto any_obj = custom_meta_type.from_void(variant.data());

    const entt::meta_any casted_value = any_obj.allow_cast(value.type());
    return casted_value == value;
}

bool match_property(QObject *object, std::string_view property_name, const entt::meta_any &value)
{
    const auto property_value = object->property(property_name.data());
    return property_value.isValid() and property_value == value;
}
} // namespace
Result<ObjectReference> ObjectTracker::find_object_by_query(const ObjectQuery &query) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};

    for (auto &&obj : tracked_objects_)
    {
        bool property_matches = true;
        for (auto &&[prop_name, prop_value] : query.properties)
        {
            if (not match_property(obj, prop_name, prop_value))
            {
                property_matches = false;
                break;
            }
        }

        if (property_matches)
        {
            LOG_DEBUG(object_tracker_logger(),
                      "TODO: write a clean abstraction to get the metatype. Qml instances have to use the superClass "
                      "to get a valid metaType");
            return ObjectReference{.object_id = reinterpret_cast<std::uintptr_t>(obj),
                                   .type_id = static_cast<meta::TypeId>(try_get_qt_meta_type(obj).id())};
        }
    }

    return make_error_result<ObjectReference>(ErrorCode::not_found,
                                              fmt::format("Could not find requested object by query {}", query));
}

Result<QObject *> ObjectTracker::get_object_by_id(probe::ObjectId obj_id) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    auto it = tracked_objects_.find(reinterpret_cast<QObject *>(obj_id));
    if (it != tracked_objects_.end())
    {
        return *it;
    }
    return make_error_result<QObject *>(ErrorCode::not_found, fmt::format("Could not find object with id {}", obj_id));
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
