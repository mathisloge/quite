// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "qt_probe_handler.hpp"
#include <QPointer>
#include <QQuickItem>
#include <QQuickItemGrabResult>
#include <QQuickWindow>
#include <quite/logger.hpp>
#include "object_tracker.hpp"
#include "property_collector.hpp"
#include "qt_meta_type_accessor.hpp"
#include "qtstdexec.hpp"
#include "to_object_id.hpp"

DEFINE_LOGGER(qt_probe_handler)

namespace quite::probe
{
AsyncResult<QImage> take_snapshot_of_qobject(QObject *object)
{
    if (object->isQuickItemType())
    {
        if (auto *item = qobject_cast<QQuickItem *>(object); item)
        {
            auto grab_job = item->grabToImage();

            co_await qobject_as_sender(grab_job.get(), &QQuickItemGrabResult::ready);
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
    co_return make_error_result(ErrorCode::not_found,
                                fmt::format("Could not capture an image from object '{}'",
                                            object != nullptr ? object->objectName().toStdString() : "unknown"));
}

QtProbeHandler::QtProbeHandler(const ObjectTracker &object_tracker)
    : object_tracker_{object_tracker}
{}

AsyncResult<entt::meta_any> QtProbeHandler::object_instance(ObjectId object_id)
{
    auto find_result = object_tracker_.get_object_by_id(object_id);
    if (find_result.has_value())
    {
        co_return entt::meta_any{std::in_place_type<QObject *>, find_result.value()};
    }
    co_return std::unexpected{std::move(find_result.error())};
}

AsyncResult<QtProbeHandler::ImageData> QtProbeHandler::take_snapshot(ObjectId object_id)
{
    auto object = object_tracker_.get_object_by_id(object_id);
    if (not object.has_value())
    {
        co_return std::unexpected{std::move(object.error())};
    }
    auto expected_image =
        co_await stdexec::starts_on(qthread_as_scheduler(object.value()->thread()), take_snapshot_of_qobject(*object));
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

AsyncResult<ObjectReference> QtProbeHandler::find_object(ObjectQuery query)
{
    auto obj_info =
        co_await (stdexec::when_all(stdexec::just(QPointer<const ObjectTracker>{std::addressof(object_tracker_)}),
                                    stdexec::just(std::move(query))) |
                  stdexec::continues_on(qthread_as_scheduler(QCoreApplication::instance()->thread())) |
                  stdexec::then([](auto &&tracker, auto &&query) -> Result<ObjectReference> {
                      if (tracker)
                      {
                          return tracker->find_object_by_query(query);
                      }
                      return make_error_result(ErrorCode::failed_precondition,
                                               "ObjectTracker was already destroyed. Probably now in shutdown.");
                  }));
    co_return obj_info;
}

AsyncResult<QtProbeHandler::PropertyMap> QtProbeHandler::fetch_properties(ObjectId object_id,
                                                                          std::vector<std::string> properties)
{
    auto obj_result = object_tracker_.get_object_by_id(object_id);
    if (not obj_result.has_value())
    {
        co_return std::unexpected{std::move(obj_result.error())};
    }
    auto collected_properties =
        co_await (stdexec::just(QPointer<QObject>{obj_result.value()}) |
                  stdexec::continues_on(qthread_as_scheduler(obj_result.value()->thread())) |
                  stdexec::then([](auto &&object) { return ObjectMeta::from_qobject(object); }) |
                  stdexec::then([properties](auto &&object_meta) -> Result<QtProbeHandler::PropertyMap> {
                      if (object_meta.meta_object == nullptr)
                      {
                          return make_error_result(ErrorCode::failed_precondition, "Could not get a QMetaObject");
                      }
                      return collect_properties(object_meta, properties);
                  }));
    co_return collected_properties;
}

AsyncResult<void> QtProbeHandler::set_property(ObjectId object_id, std::string property, entt::meta_any value)
{
    auto obj_result = object_tracker_.get_object_by_id(object_id);
    if (not obj_result.has_value())
    {
        co_return std::unexpected{std::move(obj_result.error())};
    }
    const auto result = co_await (
        stdexec::just(QPointer<QObject>{obj_result.value()}) |
        stdexec::continues_on(qthread_as_scheduler(obj_result.value()->thread())) |
        stdexec::then([](auto &&object) { return ObjectMeta::from_qobject(object); }) |
        stdexec::then([property = std::move(property), value = std::move(value)](auto &&object_meta) -> Result<void> {
            return write_property(object_meta, property, value);
        }));
    co_return result;
}

AsyncResult<std::vector<ObjectReference>> QtProbeHandler::fetch_windows()
{
    std::vector<ObjectReference> windows;
    for (auto &&obj : object_tracker_.top_level_views())
    {
        windows.emplace_back(ObjectReference{.object_id = to_object_id(obj),
                                             .type_id = static_cast<meta::TypeId>(try_get_qt_meta_type(obj).id())});
    }
    co_return windows;
}

AsyncResult<entt::meta_any> QtProbeHandler::invoke_method(entt::meta_any object,
                                                          std::string qualified_method_signature,
                                                          std::vector<entt::meta_any> params)
{
    co_return co_await (
        stdexec::when_all(stdexec::just(object), stdexec::just(qualified_method_signature), stdexec::just(params)) |
        stdexec::continues_on(qthread_as_scheduler(QCoreApplication::instance()->thread())) |
        stdexec::then([this](auto &&object, auto &&qualified_method_signature, auto &&params) {
            return method_invoker_.invoke_method(object, qualified_method_signature, params);
        }));
}

} // namespace quite::probe
