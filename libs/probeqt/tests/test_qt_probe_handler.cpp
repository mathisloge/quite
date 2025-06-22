#include <QEventLoop>
#include <QImage>
#include <QObject>
#include <boost/ut.hpp>
#include <stdexec/execution.hpp>
#include "object_tracker.hpp"
#include "qt_probe_handler.hpp"
#include "to_object_id.hpp"

using namespace boost::ut;
using namespace quite;
using namespace quite::probe;

static suite<"qtprobe QtProbeHandler"> _ = [] {
    "object_instance returns meta_any for valid object"_test = [] {
        QEventLoop loop;
        ObjectTracker tracker;
        QObject obj;
        obj.setObjectName("probe_obj");
        tracker.add_object(&obj);
        expect(loop.processEvents());

        QtProbeHandler handler{tracker};
        auto id = to_object_id(&obj);

        auto [result] = stdexec::sync_wait(handler.object_instance(id)).value();
        expect(result.has_value());
        expect(result->cast<QObject *>() == &obj);
    };

    "find_object returns correct reference"_test = [] {
        ObjectTracker tracker;
        QObject obj;
        obj.setObjectName("probe_obj");
        tracker.add_object(&obj);

        QtProbeHandler handler{tracker};
        ObjectQuery query;
        query.properties = {{"objectName", std::string{"probe_obj"}}};

        auto [result] = stdexec::sync_wait(handler.find_object(query)).value();
        expect(result.has_value());
        expect(result->object_id == to_object_id(&obj));
    };

    "fetch_windows returns all top-level views"_test = [] {
        ObjectTracker tracker;
        QObject obj1;
        obj1.setObjectName("win1");
        tracker.add_object(&obj1);

        QObject obj2;
        obj2.setObjectName("win2");
        tracker.add_object(&obj2);

        QtProbeHandler handler{tracker};
        auto [result] = stdexec::sync_wait(handler.fetch_windows()).value();
        expect(result.has_value());
        auto windows = result.value();
        expect(windows.size() == 2_u);
        expect(windows[0].object_id == to_object_id(&obj1) or windows[1].object_id == to_object_id(&obj1));
        expect(windows[0].object_id == to_object_id(&obj2) or windows[1].object_id == to_object_id(&obj2));
    };

    "fetch_properties returns property map"_test = [] {
        ObjectTracker tracker;
        QObject obj;
        obj.setObjectName("probe_obj");
        tracker.add_object(&obj);

        QtProbeHandler handler{tracker};
        auto id = to_object_id(&obj);

        std::vector<std::string> props = {"objectName"};
        auto [result] = stdexec::sync_wait(handler.fetch_properties(id, props)).value();
        expect(result.has_value());
        expect(result->contains("objectName"));
        expect((*result)["objectName"].allow_cast<QString>());
        expect((*result)["objectName"].cast<QString>() == "probe_obj");
    };

    "take_snapshot returns error for non-visual object"_test = [] {
        ObjectTracker tracker;
        QObject obj;
        obj.setObjectName("probe_obj");
        tracker.add_object(&obj);

        QtProbeHandler handler{tracker};
        auto id = to_object_id(&obj);

        auto [result] = stdexec::sync_wait(handler.take_snapshot(id)).value();
        expect(!result.has_value());
    };
};
