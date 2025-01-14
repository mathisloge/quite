#pragma once
#include <QObject>
#include <quite/async_result.hpp>

namespace quite::probe
{
enum class SnapshotErrC
{
    invalid_object
};
AsyncResult<QImage> take_snapshot(QObject *object);
} // namespace quite::probe
