#include "quite/probe.hpp"
#include "object_tracker.hpp"
#include <QtCore/private/qhooks_p.h>
#include <iostream>

namespace {

quite::ObjectTracker &objectTracker() {
  static quite::ObjectTracker tracker;
  return tracker;
}

void testAddObject(QObject *q);
void testRemoveObject(QObject *q);
void testStartup();

void installQHooks() {
  Q_ASSERT(qtHookData[QHooks::HookDataVersion] >= 1);
  Q_ASSERT(qtHookData[QHooks::HookDataSize] >= 6);

  // gammaray_next_addObject =
  // reinterpret_cast<QHooks::AddQObjectCallback>(qtHookData[QHooks::AddQObject]);
  // gammaray_next_removeObject =
  // reinterpret_cast<QHooks::RemoveQObjectCallback>(qtHookData[QHooks::RemoveQObject]);
  // gammaray_next_startup_hook =
  // reinterpret_cast<QHooks::StartupCallback>(qtHookData[QHooks::Startup]);

  qtHookData[QHooks::AddQObject] = reinterpret_cast<quintptr>(&testAddObject);
  qtHookData[QHooks::RemoveQObject] =
      reinterpret_cast<quintptr>(&testRemoveObject);
  qtHookData[QHooks::Startup] = reinterpret_cast<quintptr>(&testStartup);
}

void testAddObject(QObject *q) { objectTracker().addObject(q); }

void testRemoveObject(QObject *q) { objectTracker().removeObject(q); }

void testStartup() { std::cout << "startup" << std::endl; }

} // namespace

namespace quite {
void setupHooks() { installQHooks(); }
} // namespace quite
