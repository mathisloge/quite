#pragma once
#include <quite/disable_copy_move.hpp>
namespace quite::probe
{
class ObjectTracker;
class ProbeInstances final
{
  public:
    QUITE_DISABLE_COPY_MOVE(ProbeInstances);
    ProbeInstances(const ObjectTracker &object_tracker);
    ~ProbeInstances() = default;
};
} // namespace quite::probe
