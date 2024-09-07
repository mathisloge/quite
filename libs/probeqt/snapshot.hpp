#pragma once
#include <QObject>
#include <expected>
#include <exec/task.hpp>

namespace quite::probe
{
enum class SnapshotErrC
{
    invalid_object
};
exec::task<std::expected<QImage, SnapshotErrC>> take_snapshot(QObject *object);
} // namespace quite::probe
