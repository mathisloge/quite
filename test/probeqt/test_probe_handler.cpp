// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QColor>
#include <QCoreApplication>
#include <QEventLoop>
#include <catch2/catch_test_macros.hpp>
#include <exec/async_scope.hpp>
#include <qt_probe_handler.hpp>
#include <quite/logger.hpp>
#include "async_test_helper.hpp"
#include "object_tracker.hpp"
#include "qtstdexec.hpp"
#include "value_converters.hpp"

using namespace quite;
using namespace quite::probe;
using namespace entt::literals;

DEFINE_LOGGER(test)

namespace
{
void spin_eventloop_once()
{
    QEventLoop loop;
    REQUIRE(loop.processEvents());
}

class MyTestObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color MEMBER some_color_);

  private:
    QColor some_color_{Qt::red};
};

} // namespace
TEST_CASE("Test ProbeHandler")
{
    ObjectTracker tracker;
    register_converters(entt::locator<ValueRegistry>::emplace());
    QtProbeHandler probe_handler{tracker};

    MyTestObject test_obj{};
    const auto test_obj_id = reinterpret_cast<ObjectId>(std::addressof(test_obj));
    test_obj.setObjectName("Test");

    tracker.add_object(std::addressof(test_obj));
    spin_eventloop_once();

    SECTION("test object_instance")
    {
        ASYNC_BLOCK
        auto invalid_result = co_await probe_handler.object_instance(123);
        REQUIRE_FALSE(invalid_result.has_value());
        auto valid_result = co_await probe_handler.object_instance(test_obj_id);
        REQUIRE(valid_result.has_value());
        auto other_id = valid_result.value();
        REQUIRE(other_id == entt::forward_as_meta(static_cast<QObject *>(std::addressof(test_obj))));

        auto *casted = other_id.try_cast<QObject *>();
        REQUIRE(casted != nullptr);
        ASYNC_BLOCK_END
    }

    SECTION("test fetch_properties all")
    {
        bool do_spin{true};
        exec::async_scope scope;
        auto snd = stdexec::schedule(qthread_as_scheduler(QCoreApplication::instance()->thread())) |
                   stdexec::let_value([&]() { return probe_handler.fetch_properties(test_obj_id, {}); }) |
                   stdexec::then([&test_obj](auto &&result) {
                       REQUIRE(result.has_value());
                       const proto::IProbeHandler::PropertyMap &properties = result.value();
                       REQUIRE(properties.size() == 2);
                       const entt::meta_any &object_name_native = properties.at("objectName");
                       auto &&object_name = object_name_native.allow_cast<std::string>().cast<std::string>();
                       REQUIRE(object_name == test_obj.objectName().toStdString());

                       REQUIRE(properties.at("color") == QColor{Qt::red});
                       QCoreApplication::quit();
                   });
        scope.spawn(std::move(snd));
        QCoreApplication::exec();
    }

    SECTION("test fetch_properties filtered")
    {
        bool do_spin{true};
        exec::async_scope scope;
        const std::vector<std::string> filter{"color"};
        auto snd = stdexec::schedule(qthread_as_scheduler(QCoreApplication::instance()->thread())) |
                   stdexec::let_value([&]() { return probe_handler.fetch_properties(test_obj_id, filter); }) |
                   stdexec::then([&test_obj](auto &&result) {
                       REQUIRE(result.has_value());
                       const proto::IProbeHandler::PropertyMap &properties = result.value();
                       REQUIRE(properties.size() == 1);
                       REQUIRE(properties.at("color") == QColor{Qt::red});
                       QCoreApplication::quit();
                   });
        scope.spawn(std::move(snd));
        QCoreApplication::exec();
    }
}
#include "test_probe_handler.moc"
