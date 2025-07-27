

# File object\_tracker.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**object\_tracker.cpp**](object__tracker_8cpp.md)

[Go to the documentation of this file](object__tracker_8cpp.md)


```C++
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
#include <quite/meta_any_formatter.hpp>
#include "qt_meta_type_accessor.hpp"
#include "to_object_id.hpp"

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
    tracked_objects_.reserve(10000);
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
                .object_id = to_object_id(obj),
                .type_id = static_cast<meta::TypeId>(try_get_qt_meta_type(obj).id()),
            };
        }
    }
    return make_error_result(ErrorCode::not_found, fmt::format("Could not found object with name {}", object_name));
}

namespace
{
bool operator==(const QVariant &variant, const entt::meta_any &value)
{
    auto custom_meta_type = entt::resolve(entt::hashed_string{variant.metaType().name()}.value());
    if (not custom_meta_type)
    {
        LOG_DEBUG(object_tracker_logger(), "no custom_meta_type");
        return false;
    }
    const auto any_obj = custom_meta_type.from_void(variant.data());
    const entt::meta_any casted_value = any_obj.allow_cast(value.type());

    LOG_TRACE_L3(object_tracker_logger(),
                 "custom_meta_type: {} cmp with casted value: {}",
                 fmt::format("{}", any_obj),
                 fmt::format("{}", casted_value));
    return casted_value == value;
}

bool match_property(QObject *object, std::string_view property_name, const entt::meta_any &value)
{
    const auto property_value = object->property(property_name.cbegin());
    return property_value.isValid() and property_value == value;
}

std::string get_class_name(QObject *object)
{
    const QMetaObject *meta_obj = try_get_qt_meta_object(object);
    if (meta_obj == nullptr)
    {
        return {};
    }

    std::string_view class_name = meta_obj->className();
    // Remove QML-generated suffixes
    if (auto pos = class_name.find("_QMLTYPE_"); pos != std::string_view::npos)
    {
        class_name = class_name.substr(0, pos);
    }
    else if (auto pos = class_name.find("_QML_"); pos != std::string_view::npos)
    {
        class_name = class_name.substr(0, pos);
    }
    return std::string{class_name};
}
} // namespace
Result<ObjectReference> ObjectTracker::find_object_by_query(const ObjectQuery &query) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};

    // Helper function to recursively match the parent hierarchy
    const auto match_parent_hierarchy = [](QObject *object, const std::shared_ptr<ObjectQuery> &query) -> bool {
        QObject *current_parent = object->parent();
        auto current_query = query;

        while (current_query && current_parent)
        {
            bool matched =
                current_query->type_name.empty() or
                (not current_query->type_name.empty() and get_class_name(current_parent) == current_query->type_name);
            if (matched)
            {
                // Check if the current parent matches the current query
                for (auto &&[prop_name, prop_value] : current_query->properties)
                {
                    if (not match_property(current_parent, prop_name, prop_value))
                    {
                        current_parent = current_parent->parent();
                        matched = false;
                        break;
                    }
                    matched = true;
                }
            }

            if (matched)
            {
                // Move up the hierarchy
                current_parent = current_parent->parent();
                current_query = current_query->container;
            }
        }

        return current_query == nullptr;
    };

    for (auto &&obj : tracked_objects_)
    {
        // First, check if the parent hierarchy matches
        if (query.container && !match_parent_hierarchy(obj, query.container))
        {
            continue;
        }
        const bool name_matched =
            query.type_name.empty() or (not query.type_name.empty() and get_class_name(obj) == query.type_name);

        // Then, check if the properties of the current object match
        bool property_matches = true;
        if (name_matched)
        {
            for (auto &&[prop_name, prop_value] : query.properties)
            {
                if (not match_property(obj, prop_name, prop_value))
                {
                    property_matches = false;
                    break;
                }
            }
        }

        if (name_matched and property_matches)
        {
            return ObjectReference{.object_id = to_object_id(obj),
                                   .type_id = static_cast<meta::TypeId>(try_get_qt_meta_type(obj).id())};
        }
    }

    return make_error_result(ErrorCode::not_found, fmt::format("Could not find requested object by query {}", query));
}

Result<QObject *> ObjectTracker::get_object_by_id(ObjectId obj_id) const
{
    std::shared_lock l{locker_};
    InOwnContext c{own_ctx_};
    auto it = tracked_objects_.find(from_object_id(obj_id));
    if (it != tracked_objects_.end())
    {
        return *it;
    }
    return make_error_result(ErrorCode::not_found, fmt::format("Could not find object with id {}", obj_id));
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
    QMetaObject::invokeMethod(this, &ObjectTracker::process_new_objects, Qt::ConnectionType::QueuedConnection);
}
} // namespace quite::probe
```


