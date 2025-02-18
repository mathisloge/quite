#include "object_handler.hpp"
#include <QQuickItem>
#include <QQuickItemGrabResult>
#include <QQuickWindow>
#include "object_tracker.hpp"
#include "qtstdexec.h"

namespace quite::probe
{
AsyncResult<QImage> take_snapshot_of_qobject(QObject *object)
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

ObjectHandler::ObjectHandler(const ObjectTracker &object_tracker)
    : object_tracker_{object_tracker}
{}

AsyncResult<ObjectHandler::ImageData> ObjectHandler::take_snapshot(ObjectId object_id)
{
    auto object =
        co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                               [this, object_id]() { return object_tracker_.get_object_by_id(object_id); });

    if (not object.has_value())
    {
        co_return std::unexpected{std::move(object.error())};
    }
    auto expected_image = co_await stdexec::starts_on(
        QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread()), take_snapshot_of_qobject(*object));
    if (not expected_image.has_value())
    {
        co_return std::unexpected{std::move(expected_image.error())};
    }

    expected_image->convertTo(QImage::Format::Format_RGBA8888);
    ImageData image{.width = static_cast<std::uint32_t>(expected_image->width()),
                    .height = static_cast<std::uint32_t>(expected_image->height())};
    image.image_data.reserve(expected_image->sizeInBytes());
    std::span<const std::uint8_t> data_view{expected_image->bits(),
                                            static_cast<std::size_t>(expected_image->sizeInBytes())};
    std::ranges::copy(data_view, std::back_inserter(image.image_data));
    co_return image;
}
} // namespace quite::probe
