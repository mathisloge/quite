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

static suite<"qtprobe"> _ = [] { // NOLINT
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
