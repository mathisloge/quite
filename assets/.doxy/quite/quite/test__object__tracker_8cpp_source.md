

# File test\_object\_tracker.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**tests**](dir_c1613d43beada98aaa8aaa25db1fb827.md) **>** [**test\_object\_tracker.cpp**](test__object__tracker_8cpp.md)

[Go to the documentation of this file](test__object__tracker_8cpp.md)


```C++
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

class MyCustomClass : public QObject
{
    Q_OBJECT
};

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

    "find object by query with type name"_test = [] {
        QEventLoop loop;
        ObjectTracker tracker;

        QObject a1;
        MyCustomClass my_class;
        QObject a2;
        tracker.add_object(&a1);
        tracker.add_object(&my_class);
        tracker.add_object(&a2);
        expect(loop.processEvents());

        auto &&query = make_query().with_type("MyCustomClass");
        auto found = tracker.find_object_by_query(query);
        expect(found.has_value());
        expect(found->object_id == to_object_id(&my_class));
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
#include "test_object_tracker.moc"
```


