#pragma once
#include <QObject>
#include <QTimer>
#include <unordered_set>
#include <shared_mutex>

namespace quite
{
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

    std::unordered_map<std::string, std::string> findObject(const std::string& object_name);

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
