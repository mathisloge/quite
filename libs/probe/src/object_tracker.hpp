#pragma once
#include <QObject>

namespace quite {
class ObjectTracker final {
public:
  void addObject(QObject *);
  void removeObject(QObject *);
};
} // namespace quite
