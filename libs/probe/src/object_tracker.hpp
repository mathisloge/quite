#pragma once
#include <QObject>
#include <QTimer>
#include <expected>
#include <shared_mutex>
#include <unordered_set>
#include "object_id.hpp"
#include "quite/proto/probe.pb.h"

namespace quite
{
struct ObjectInfo
{
    std::uintptr_t object_id;
    std::string class_type;
};

enum class ObjectErrC
{
    not_found
};
class ObjectTracker final : public QObject
{
    Q_OBJECT
  public:
    ObjectTracker();
    ~ObjectTracker() override;

    void add_object(QObject *);
    void remove_object(QObject *);
    void begin_context();
    void end_context();

    const std::unordered_set<QObject *> &top_level_views() const;

    std::expected<ObjectInfo, ObjectErrC> find_object(const std::string &object_name);

    std::expected<ObjectInfo, ObjectErrC> find_object_by_query(const proto::ObjectSearchQuery &query);
    std::expected<QObject *, ObjectErrC> get_object_by_id(probe::ObjectId obj_id);
    std::expected<std::string, ObjectErrC> get_property(probe::ObjectId obj_id, const std::string &property_name);

  private:
    void start_timer();
    void process_new_objects();

  private:
    std::atomic_bool own_ctx_{false};
    std::shared_mutex locker_;
    QTimer init_timer_;
    std::unordered_set<QObject *> objects_to_track_;
    std::unordered_set<QObject *> tracked_objects_;
    std::unordered_set<QObject *> top_level_views_;
};
} // namespace quite
