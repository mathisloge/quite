#pragma once
#include <QObject>
#include <exec/task.hpp>
#include <expected>

namespace quite::probe
{
enum class SnapshotErrC {
    invalid_object
};
exec::task<std::expected<QImage, SnapshotErrC>> take_snapshot(QObject *object);
}
