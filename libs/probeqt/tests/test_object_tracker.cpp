#include <QEventLoop>
#include <catch2/catch_test_macros.hpp>
#include <quite/value/object_query.hpp>
#include "object_tracker.hpp"
#include "to_object_id.hpp"

using namespace quite;
using namespace quite::probe;

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
