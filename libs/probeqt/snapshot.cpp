#include "snapshot.hpp"
#include <QQuickItem>
#include <QQuickItemGrabResult>
#include <QQuickWindow>
#include "qtstdexec.h"

namespace quite::probe
{
AsyncResult<QImage> take_snapshot(QObject *object)
{
    if (object->isQuickItemType())
    {
        if (auto *item = qobject_cast<QQuickItem *>(object); item)
        {
            auto grab_job = item->grabToImage();

            co_await QtStdExec::qObjectAsSender(grab_job.get(), &QQuickItemGrabResult::ready);
            co_return grab_job->image();
        }
    }
    else if (object->isWindowType())
    {
        if (auto &&item = qobject_cast<QQuickWindow *>(object); item)
        {
            auto grabbed_image = item->grabWindow();
            co_return grabbed_image;
        }
    }
    co_return make_error_result<QImage>(
        ErrorCode::not_found,
        fmt::format("Could not capture an image from object '{}'",
                    object != nullptr ? object->objectName().toStdString() : "unknown"));
}
} // namespace quite::probe
