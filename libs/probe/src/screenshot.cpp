#include "screenshot.hpp"
#include <QQuickItem>
#include <QQuickItemGrabResult>
#include "qtstdexec.h"
namespace quite::probe
{
exec::task<std::expected<QImage, SnapshotErrC>> take_snapshot(QObject *object)
{
    if (object->isQuickItemType())
    {
        auto item = qobject_cast<QQuickItem *>(object);
        if (!item)
        {
        }
        auto grab_job = item->grabToImage();

        co_await QtStdExec::qObjectAsSender(grab_job.get(), &QQuickItemGrabResult::ready);
        co_return grab_job->image();

    }
    co_return std::unexpected(SnapshotErrC::invalid_object);
}
} // namespace quite::probe
