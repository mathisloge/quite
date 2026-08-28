// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QEventLoop>
#include <QImage>
#include <QObject>
#include <exec/async_scope.hpp>
#include <exec/inline_scheduler.hpp>
#include <gtest/gtest.h>
#include <stdexec/execution.hpp>
#include "object_tracker.hpp"
#include "qt_probe_handler.hpp"
#include "to_object_id.hpp"

using namespace quite;
using namespace quite::probe;

namespace
{
class QtProbeHandlerTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        obj_.setObjectName("probe_obj");
        tracker_.add_object(&obj_);
        ASSERT_TRUE(loop_.processEvents());
    }

    QEventLoop loop_;
    ObjectTracker tracker_;
    QObject obj_;
};
} // namespace

TEST_F(QtProbeHandlerTest, ObjectInstanceReturnsMetaAnyForValidObject)
{
    QtProbeHandler handler{tracker_};
    auto id = to_object_id(&obj_);

    auto [result] = stdexec::sync_wait(handler.object_instance(id)).value();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->cast<QObject *>(), &obj_);
}

TEST_F(QtProbeHandlerTest, FindObjectReturnsCorrectReference)
{
    QtProbeHandler handler{tracker_};
    ObjectQuery query;
    query.properties = {{"objectName", std::string{"probe_obj"}}};

    exec::async_scope scope;
    auto wait_senders = scope.on_empty();
    ObjectReference found_obj{};
    scope.spawn(stdexec::starts_on(exec::inline_scheduler{},
                                   handler.find_object(query) | stdexec::then([&found_obj](auto &&result) {
                                       EXPECT_TRUE(result.has_value());
                                       found_obj = result.value();
                                   })));
    EXPECT_TRUE(loop_.processEvents());
    stdexec::sync_wait(wait_senders);

    EXPECT_EQ(found_obj.object_id, to_object_id(&obj_));
}

TEST_F(QtProbeHandlerTest, WriteProperty)
{
    QtProbeHandler handler{tracker_};
    ObjectQuery query;
    query.properties = {{"objectName", std::string{"probe_obj"}}};

    exec::async_scope scope;
    auto wait_senders = scope.on_empty();
    const std::string new_name{"testName"};
    scope.spawn(stdexec::starts_on(exec::inline_scheduler{},
                                   handler.set_property(to_object_id(&obj_), "objectName", new_name)) |
                stdexec::then([&](auto &&result) {
                    EXPECT_TRUE(result.has_value());
                    const auto actual_name = obj_.objectName().toStdString();
                    EXPECT_EQ(actual_name, new_name);
                }));
    EXPECT_TRUE(loop_.processEvents());
    stdexec::sync_wait(wait_senders);
}

#if 0
TEST(QtProbeHandler, FetchWindowsReturnsAllTopLevelViews)
{
    QEventLoop loop;
    ObjectTracker tracker;
    QObject obj1;
    obj1.setObjectName("win1");
    tracker.add_object(&obj1);

    QObject obj2;
    obj2.setObjectName("win2");
    tracker.add_object(&obj2);

    EXPECT_TRUE(loop.processEvents());

    QtProbeHandler handler{tracker};
    auto [result] = stdexec::sync_wait(handler.fetch_windows()).value();
    ASSERT_TRUE(result.has_value());
    auto windows = result.value();
    ASSERT_EQ(windows.size(), 2u);
    EXPECT_TRUE(windows[0].object_id == to_object_id(&obj1) || windows[1].object_id == to_object_id(&obj1));
    EXPECT_TRUE(windows[0].object_id == to_object_id(&obj2) || windows[1].object_id == to_object_id(&obj2));
}

TEST_F(QtProbeHandlerTest, FetchPropertiesReturnsPropertyMap)
{
    QtProbeHandler handler{tracker_};
    auto id = to_object_id(&obj_);

    std::vector<std::string> props = {"objectName"};
    auto [result] = stdexec::sync_wait(handler.fetch_properties(id, props)).value();
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->contains("objectName"));
    EXPECT_TRUE((*result)["objectName"].allow_cast<QString>());
    EXPECT_EQ((*result)["objectName"].cast<QString>(), "probe_obj");
}

TEST_F(QtProbeHandlerTest, TakeSnapshotReturnsErrorForNonVisualObject)
{
    QtProbeHandler handler{tracker_};
    auto id = to_object_id(&obj_);

    auto [result] = stdexec::sync_wait(handler.take_snapshot(id)).value();
    EXPECT_FALSE(result.has_value());
}
#endif
