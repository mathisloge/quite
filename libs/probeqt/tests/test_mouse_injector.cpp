// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QEventLoop>
#include <QMouseEvent>
#include <QObject>
#include <gtest/gtest.h>
#include <stdexec/execution.hpp>
#include "injector/mouse_injector.hpp"
#include "object_tracker.hpp"
#include "to_object_id.hpp"

using namespace quite;
using namespace quite::probe;
using namespace quite::core;

namespace
{
struct RecordedMouseEvent
{
    QEvent::Type type;
    QPointF position;
    Qt::MouseButton button;
    Qt::KeyboardModifiers modifiers;
};

class RecordingObject final : public QObject
{
  public:
    bool eventFilter(QObject * /*watched*/, QEvent *event) override
    {
        if (auto *mouse_event = dynamic_cast<QMouseEvent *>(event))
        {
            events.push_back(RecordedMouseEvent{
                mouse_event->type(), mouse_event->position(), mouse_event->button(), mouse_event->modifiers()});
        }
        return false;
    }

    std::vector<RecordedMouseEvent> events;
};

class MouseInjectorTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        target_.setObjectName("target");
        target_.installEventFilter(&recorder_);
        tracker_.add_object(&target_);
        ASSERT_TRUE(loop_.processEvents());
    }

    Result<void> run_action(MouseAction action)
    {
        MouseInjector injector{tracker_};
        auto [result] = stdexec::sync_wait(injector.single_action(to_object_id(&target_), std::move(action))).value();
        loop_.processEvents();
        return result;
    }

    QEventLoop loop_;
    ObjectTracker tracker_;
    QObject target_;
    RecordingObject recorder_;
};
} // namespace

TEST_F(MouseInjectorTest, ClickPostsPressThenRelease)
{
    auto result = run_action(MouseAction{.position = {1, 2},
                                         .button = MouseButton::left,
                                         .trigger = MouseTrigger::click,
                                         .modifier = KeyboardModifier::none});

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(recorder_.events.size(), 2u);
    EXPECT_EQ(recorder_.events[0].type, QEvent::MouseButtonPress);
    EXPECT_EQ(recorder_.events[1].type, QEvent::MouseButtonRelease);
}

TEST_F(MouseInjectorTest, DoubleClickPostsSingleEvent)
{
    auto result = run_action(MouseAction{.position = {1, 2},
                                         .button = MouseButton::left,
                                         .trigger = MouseTrigger::double_click,
                                         .modifier = KeyboardModifier::none});

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(recorder_.events.size(), 1u);
    EXPECT_EQ(recorder_.events[0].type, QEvent::MouseButtonDblClick);
}

TEST_F(MouseInjectorTest, MoveUsesRequestedPosition)
{
    auto result = run_action(MouseAction{.position = {5, 7},
                                         .button = MouseButton::left,
                                         .trigger = MouseTrigger::move,
                                         .modifier = KeyboardModifier::none});

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(recorder_.events.size(), 1u);
    EXPECT_EQ(recorder_.events[0].position, QPointF(5, 7));
}

TEST_F(MouseInjectorTest, NoneTriggerPostsNoEvent)
{
    auto result = run_action(MouseAction{.position = {1, 2},
                                         .button = MouseButton::left,
                                         .trigger = MouseTrigger::none,
                                         .modifier = KeyboardModifier::none});

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(recorder_.events.empty());
}

TEST_F(MouseInjectorTest, UnknownTargetReturnsError)
{
    MouseInjector injector{tracker_};
    auto [result] = stdexec::sync_wait(injector.single_action(ObjectId{999999},
                                                              MouseAction{.position = {0, 0},
                                                                          .button = MouseButton::left,
                                                                          .trigger = MouseTrigger::click,
                                                                          .modifier = KeyboardModifier::none}))
                        .value();

    EXPECT_FALSE(result.has_value());
}

TEST_F(MouseInjectorTest, RightClickUsesRightMouseButton)
{
    auto result = run_action(MouseAction{.position = {1, 2},
                                         .button = MouseButton::right,
                                         .trigger = MouseTrigger::click,
                                         .modifier = KeyboardModifier::none});

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(recorder_.events.size(), 2u);
    EXPECT_EQ(recorder_.events[0].button, Qt::RightButton);
}

TEST_F(MouseInjectorTest, ShiftModifierIsForwardedToEvent)
{
    auto result = run_action(MouseAction{.position = {1, 2},
                                         .button = MouseButton::left,
                                         .trigger = MouseTrigger::click,
                                         .modifier = KeyboardModifier::shift});

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(recorder_.events.size(), 2u);
    EXPECT_TRUE(recorder_.events[0].modifiers.testFlag(Qt::ShiftModifier));
}
