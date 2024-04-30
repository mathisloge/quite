#pragma once
#include <QObject>
#include <QTimer>
#include <expected>
#include <shared_mutex>
#include <unordered_set>

namespace quite
{
struct ObjectInfo
{
    std::string class_type;
    std::unordered_map<std::string, std::string> properties;
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

    std::expected<ObjectInfo, ObjectErrC> findObject(const std::string &object_name);

  private:
    void startTimer();
    void processNewObjects();

  private:
    std::atomic_bool own_ctx_{false};
    std::shared_mutex locker_;
    QTimer init_timer_;
    std::unordered_set<QObject *> objects_to_track_;
    std::unordered_set<QObject *> tracked_objects_;
};
} // namespace quite
