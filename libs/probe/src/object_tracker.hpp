#pragma once
#include <QObject>
#include <QTimer>
#include <expected>
#include <shared_mutex>
#include <unordered_set>
#include "object_id.hpp"

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

    void addObject(QObject *);
    void removeObject(QObject *);
    void beginContext();
    void endContext();

    const std::unordered_set<QObject *> &top_level_views() const;

    std::expected<ObjectInfo, ObjectErrC> findObject(const std::string &object_name);
    std::expected<QObject *, ObjectErrC> get_object_by_id(probe::ObjectId obj_id);
    std::expected<std::string, ObjectErrC> get_property(probe::ObjectId obj_id, const std::string &property_name);

  private:
    void startTimer();
    void processNewObjects();

  private:
    std::atomic_bool own_ctx_{false};
    std::shared_mutex locker_;
    QTimer init_timer_;
    std::unordered_set<QObject *> objects_to_track_;
    std::unordered_set<QObject *> tracked_objects_;
    std::unordered_set<QObject *> top_level_views_;
};
} // namespace quite
