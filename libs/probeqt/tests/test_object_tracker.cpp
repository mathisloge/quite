// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QEventLoop>
#include <gtest/gtest.h>
#include <quite/error.hpp>
#include <quite/value/object_query.hpp>
#include "object_tracker.hpp"
#include "to_object_id.hpp"

using namespace quite;
using namespace quite::probe;

class MyCustomClass : public QObject
{
    Q_OBJECT
};

TEST(ObjectTracker, FindObjectByName)
{
    QEventLoop loop;
    ObjectTracker tracker;

    QObject obj1;
    obj1.setObjectName("obj1");
    tracker.add_object(&obj1);

    QObject obj2;
    obj2.setObjectName("obj2");
    tracker.add_object(&obj2);

    EXPECT_TRUE(loop.processEvents());

    auto found1 = tracker.find_object("obj1");
    ASSERT_TRUE(found1.has_value());
    EXPECT_EQ(found1->object_id, to_object_id(&obj1));

    auto found2 = tracker.find_object("obj2");
    ASSERT_TRUE(found2.has_value());
    EXPECT_EQ(found2->object_id, to_object_id(&obj2));
}

TEST(ObjectTracker, FindObjectByQueryFlat)
{
    QEventLoop loop;
    ObjectTracker tracker;

    QObject obj1;
    obj1.setObjectName("obj1");
    tracker.add_object(&obj1);

    QObject obj2;
    obj2.setObjectName("obj2");
    tracker.add_object(&obj2);

    EXPECT_TRUE(loop.processEvents());

    ObjectQuery query;
    query.properties = {{"objectName", std::string{"obj2"}}};
    auto found = tracker.find_object_by_query(query);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->object_id, to_object_id(&obj2));
}

TEST(ObjectTracker, FindObjectByQueryWithParentContainer)
{
    QEventLoop loop;
    ObjectTracker tracker;

    QObject parent;
    parent.setObjectName("parent");
    tracker.add_object(&parent);

    QObject child(&parent);
    child.setObjectName("child");
    tracker.add_object(&child);

    QObject child2;
    child2.setObjectName("child");
    tracker.add_object(&child2);

    EXPECT_TRUE(loop.processEvents());

    auto parent_query = std::make_shared<ObjectQuery>();
    parent_query->properties = {{"objectName", std::string{"parent"}}};

    ObjectQuery query;
    query.container = parent_query;
    query.properties = {{"objectName", std::string{"child"}}};

    auto found = tracker.find_object_by_query(query);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->object_id, to_object_id(&child));
}

TEST(ObjectTracker, FindObjectByQueryWithMultipleParents)
{
    QEventLoop loop;
    ObjectTracker tracker;

    QObject grandparent;
    grandparent.setObjectName("grandparent");
    tracker.add_object(&grandparent);

    QObject parent(&grandparent);
    parent.setObjectName("parent");
    tracker.add_object(&parent);

    QObject child(&parent);
    child.setObjectName("child");
    tracker.add_object(&child);

    QObject child2;
    child2.setObjectName("child");
    tracker.add_object(&child2);

    EXPECT_TRUE(loop.processEvents());

    auto grandparent_query = std::make_shared<ObjectQuery>();
    grandparent_query->properties = {{"objectName", std::string{"grandparent"}}};

    auto parent_query = std::make_shared<ObjectQuery>();
    parent_query->container = grandparent_query;
    parent_query->properties = {{"objectName", std::string{"parent"}}};

    ObjectQuery query;
    query.container = parent_query;
    query.properties = {{"objectName", std::string{"child"}}};

    auto found = tracker.find_object_by_query(query);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->object_id, to_object_id(&child));
}

TEST(ObjectTracker, FindObjectByQueryWithTypeName)
{
    QEventLoop loop;
    ObjectTracker tracker;

    QObject a1;
    MyCustomClass my_class;
    QObject a2;
    tracker.add_object(&a1);
    tracker.add_object(&my_class);
    tracker.add_object(&a2);
    EXPECT_TRUE(loop.processEvents());

    auto &&type_query = query().type("MyCustomClass");
    auto found = tracker.find_object_by_query(type_query);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->object_id, to_object_id(&my_class));
}

TEST(ObjectTracker, RemoveObject)
{
    QEventLoop loop;
    ObjectTracker tracker;

    QObject obj;
    obj.setObjectName("to_remove");
    tracker.add_object(&obj);

    EXPECT_TRUE(loop.processEvents());

    auto found = tracker.find_object("to_remove");
    EXPECT_TRUE(found.has_value());

    tracker.remove_object(&obj);

    auto not_found = tracker.find_object("to_remove");
    EXPECT_FALSE(not_found.has_value());
}

#include "test_object_tracker.moc"
