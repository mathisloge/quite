#pragma once
#include <QObject>
#include <QTimer>
#include <expected>
#include <shared_mutex>
#include <unordered_set>
#include <quite/meta/meta_type_id.hpp>
#include <quite/result.hpp>
#include <quite/value/object_id.hpp>
#include <quite/value/object_query.hpp>
#include "object_id.hpp"

namespace quite::probe
{
struct ObjectInfo
{
    std::uintptr_t object_id;
    meta::TypeId class_type;
};

enum class ObjectErrC
{
    not_found
};
class ObjectTracker final : public QObject
{
    Q_OBJECT
  public:
    Q_DISABLE_COPY_MOVE(ObjectTracker)
    ObjectTracker();
    ~ObjectTracker() override;

    void add_object(QObject *);
    void remove_object(QObject *);
    void begin_context();
    void end_context();

    const std::unordered_set<QObject *> &top_level_views() const;
    Result<ObjectInfo> find_object(const std::string &object_name) const;
    Result<ObjectReference> find_object_by_query(const ObjectQuery &query) const;
    Result<QObject *> get_object_by_id(probe::ObjectId obj_id) const;
    std::expected<std::string, ObjectErrC> get_property(probe::ObjectId obj_id, const std::string &property_name) const;

  private:
    void start_timer();
    void process_new_objects();

  private:
    mutable std::atomic_bool own_ctx_{false};
    mutable std::shared_mutex locker_;
    QTimer init_timer_;
    std::unordered_set<QObject *> objects_to_track_;
    std::unordered_set<QObject *> tracked_objects_;
    std::unordered_set<QObject *> top_level_views_;
};
} // namespace quite::probe
