#include <QEventLoop>
#include <boost/ut.hpp>
#include <quite/error.hpp>
#include <quite/value/object_query.hpp>
#include "object_tracker.hpp"
#include "to_object_id.hpp"

using namespace quite;
using namespace quite::probe;

using namespace quite;
using namespace boost::ut;
using namespace std::literals::string_view_literals;

static suite<"qtprobe"> _ = [] {
    "find object by name"_test = [] {
        QEventLoop loop;
        ObjectTracker tracker;

        QObject obj1;
        obj1.setObjectName("obj1");
        tracker.add_object(&obj1);

        QObject obj2;
        obj2.setObjectName("obj2");
        tracker.add_object(&obj2);

        expect(loop.processEvents());

        auto found1 = tracker.find_object("obj1");
        expect(found1.has_value());
        expect(found1->object_id == to_object_id(&obj1));

        auto found2 = tracker.find_object("obj2");
        expect(found2.has_value());
        expect(found2->object_id == to_object_id(&obj2));
    };

    "find object by query (flat)"_test = [] {
        QEventLoop loop;
        ObjectTracker tracker;

        QObject obj1;
        obj1.setObjectName("obj1");
        tracker.add_object(&obj1);

        QObject obj2;
        obj2.setObjectName("obj2");
        tracker.add_object(&obj2);

        expect(loop.processEvents());

        ObjectQuery query;
        query.properties = {{"objectName", std::string{"obj2"}}};
        auto found = tracker.find_object_by_query(query);
        expect(found.has_value());
        expect(found->object_id == to_object_id(&obj2));
    };

    "find object by query with parent (container)"_test = [] {
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

        expect(loop.processEvents());

        auto parent_query = std::make_shared<ObjectQuery>();
        parent_query->properties = {{"objectName", std::string{"parent"}}};

        ObjectQuery query;
        query.container = parent_query;
        query.properties = {{"objectName", std::string{"child"}}};

        auto found = tracker.find_object_by_query(query);
        expect(found.has_value());
        expect(found->object_id == to_object_id(&child));
    };

    "find object by query with multiple parents"_test = [] {
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

        expect(loop.processEvents());

        auto grandparent_query = std::make_shared<ObjectQuery>();
        grandparent_query->properties = {{"objectName", std::string{"grandparent"}}};

        auto parent_query = std::make_shared<ObjectQuery>();
        parent_query->container = grandparent_query;
        parent_query->properties = {{"objectName", std::string{"parent"}}};

        ObjectQuery query;
        query.container = parent_query;
        query.properties = {{"objectName", std::string{"child"}}};

        auto found = tracker.find_object_by_query(query);
        expect(found.has_value());
        expect(found->object_id == to_object_id(&child));
    };

    "remove object"_test = [] {
        QEventLoop loop;
        ObjectTracker tracker;

        QObject obj;
        obj.setObjectName("to_remove");
        tracker.add_object(&obj);

        expect(loop.processEvents());

        auto found = tracker.find_object("to_remove");
        expect(found.has_value());

        tracker.remove_object(&obj);

        auto not_found = tracker.find_object("to_remove");
        expect(!not_found.has_value());
    };
};

#if 0
TEST_CASE("Find object by name", "[Qt,ObjectTracker]")
{
    QEventLoop loop;
    ObjectTracker object_tracker;

    QObject test_obj1{};
    test_obj1.setObjectName("test_obj1");
    object_tracker.add_object(&test_obj1);

    QObject test_obj2{};
    test_obj2.setObjectName("test_obj2");
    object_tracker.add_object(&test_obj2);

    REQUIRE(loop.processEvents());

    auto find_obj1 = object_tracker.find_object("test_obj1");
    REQUIRE(find_obj1.has_value());
    REQUIRE(find_obj1->object_id == to_object_id(std::addressof(test_obj1)));

    auto find_obj2 = object_tracker.find_object("test_obj2");
    REQUIRE(find_obj2.has_value());
    REQUIRE(find_obj2->object_id == to_object_id(std::addressof(test_obj2)));

    QObject test_obj3{};
    test_obj3.setObjectName("test_obj1");
    object_tracker.add_object(&test_obj3);

    REQUIRE(loop.processEvents());

    auto find_obj1_3 = object_tracker.find_object("test_obj1");
    REQUIRE(find_obj1_3.has_value());
    // now it's just one of them. order depends on the given id hash
    REQUIRE((find_obj1_3->object_id == to_object_id(std::addressof(test_obj3)) or
             find_obj1_3->object_id == to_object_id(std::addressof(test_obj1))));

    object_tracker.remove_object(std::addressof(test_obj1));

    find_obj1_3 = object_tracker.find_object("test_obj1");
    REQUIRE(find_obj1_3.has_value());
    REQUIRE(find_obj1_3->object_id == to_object_id(std::addressof(test_obj3)));
}

TEST_CASE("Find object by query", "[Qt,ObjectTracker]")
{
    QEventLoop loop;
    ObjectTracker object_tracker;

    QObject test_obj1{};
    test_obj1.setObjectName("test_obj1");
    object_tracker.add_object(&test_obj1);

    QObject test_obj2_copy{};
    test_obj2_copy.setObjectName("test_obj2");
    object_tracker.add_object(&test_obj2_copy);

    QObject test_obj2{&test_obj1};
    test_obj2.setObjectName("test_obj2");
    object_tracker.add_object(&test_obj2);

    REQUIRE(loop.processEvents());

    auto query_obj1 = std::make_shared<ObjectQuery>();
    query_obj1->properties = {{"objectName", std::string{"test_obj1"}}};

    auto find_obj_copy =
        object_tracker.find_object_by_query(ObjectQuery{.properties = {{"objectName", std::string{"test_obj2"}}}});

    REQUIRE(find_obj_copy.has_value());
    REQUIRE(find_obj_copy->object_id == to_object_id(&test_obj2_copy));

    auto find_obj_with_container = object_tracker.find_object_by_query(
        ObjectQuery{.container = query_obj1, .properties = {{"objectName", std::string{"test_obj2"}}}});

    REQUIRE(find_obj_with_container.has_value());
    REQUIRE(find_obj_with_container->object_id == to_object_id(&test_obj2));
}

TEST_CASE("Find object by query with multiple parents", "[Qt,ObjectTracker]")
{
    QEventLoop loop;
    ObjectTracker object_tracker;

    QObject test_obj1{};
    test_obj1.setObjectName("test_obj1");
    object_tracker.add_object(&test_obj1);

    QObject test_obj2{&test_obj1};
    test_obj2.setObjectName("test_obj2");
    object_tracker.add_object(&test_obj2);

    QObject test_obj3{&test_obj2};
    test_obj3.setObjectName("test_obj3");
    object_tracker.add_object(&test_obj3);

    QObject test_obj3_cpy{};
    test_obj3_cpy.setObjectName("test_obj3");
    object_tracker.add_object(&test_obj3_cpy);

    REQUIRE(loop.processEvents());

    auto query_obj1 = std::make_shared<ObjectQuery>();
    query_obj1->properties = {{"objectName", std::string{"test_obj1"}}};

    auto query_obj3 = object_tracker.find_object_by_query(
        ObjectQuery{.container = query_obj1, .properties = {{"objectName", std::string{"test_obj3"}}}});

    REQUIRE(query_obj3.has_value());
    REQUIRE(query_obj3->object_id == to_object_id(&test_obj3));
}
#endif
