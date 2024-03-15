#pragma once
#include <QObject>
#include <QTimer>
#include <unordered_set>

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

  private:
    void startTimer();
    void processNewObjects();

  private:
    std::atomic_bool own_ctx_{false};
    std::mutex locker_;
    QTimer init_timer_;
    std::unordered_set<QObject *> objects_to_track_;
    std::unordered_set<QObject *> tracked_objects_;
};
} // namespace quite
