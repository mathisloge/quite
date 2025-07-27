// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QEventLoop>
#include <QImage>
#include <QObject>
#include <boost/ut.hpp>
#include <exec/async_scope.hpp>
#include <stdexec/execution.hpp>
#include "object_tracker.hpp"
#include "qt_probe_handler.hpp"
#include "to_object_id.hpp"

using namespace boost::ut;
using namespace quite;
using namespace quite::probe;

static suite<"qtprobe QtProbeHandler"> _ = [] {
    QEventLoop loop;
    ObjectTracker tracker;
    QObject obj;
    obj.setObjectName("probe_obj");
    tracker.add_object(&obj);
    expect(loop.processEvents());

    "object_instance returns meta_any for valid object"_test = [&] {
        QtProbeHandler handler{tracker};
        auto id = to_object_id(&obj);

        auto [result] = stdexec::sync_wait(handler.object_instance(id)).value();
        expect(result.has_value());
        expect(result->cast<QObject *>() == &obj);
    };

    "find_object returns correct reference"_test = [&] {
        fmt::println("find_object");
        QtProbeHandler handler{tracker};
        ObjectQuery query;
        query.properties = {{"objectName", std::string{"probe_obj"}}};

        exec::async_scope scope;
        auto wait_senders = scope.on_empty();
        ObjectReference found_obj{};
        scope.spawn(stdexec::starts_on(exec::inline_scheduler{},
                                       handler.find_object(query) | stdexec::then([&found_obj](auto &&result) {
                                           expect(result.has_value());
                                           found_obj = result.value();
                                       })));
        expect(loop.processEvents());
        stdexec::sync_wait(wait_senders);

        expect(found_obj.object_id == to_object_id(&obj));
    };

    "write property"_test = [&] {
        fmt::println("find_object");
        QtProbeHandler handler{tracker};
        ObjectQuery query;
        query.properties = {{"objectName", std::string{"probe_obj"}}};

        exec::async_scope scope;
        auto wait_senders = scope.on_empty();
        const std::string new_name{"testName"};
        scope.spawn(stdexec::starts_on(exec::inline_scheduler{},
                                       handler.set_property(to_object_id(&obj), "objectName", new_name)) |
                    stdexec::then([&](auto &&result) {
                        expect(result.has_value());
                        const auto actual_name = obj.objectName().toStdString();
                        expect(actual_name == new_name);
                    }));
        expect(loop.processEvents());
        stdexec::sync_wait(wait_senders);
    };
#if 0
    "fetch_windows returns all top-level views"_test = [&] {
        QEventLoop loop;
        fmt::println("fetch_windows");
        ObjectTracker tracker;
        QObject obj1;
        obj1.setObjectName("win1");
        tracker.add_object(&obj1);

        QObject obj2;
        obj2.setObjectName("win2");
        tracker.add_object(&obj2);

        expect(loop.processEvents());

        QtProbeHandler handler{tracker};
        auto [result] = stdexec::sync_wait(handler.fetch_windows()).value();
        expect(result.has_value());
        auto windows = result.value();
        if (not expect(windows.size() == 2_u))
        {
            return;
        }
        expect(windows[0].object_id == to_object_id(&obj1) or windows[1].object_id == to_object_id(&obj1));
        expect(windows[0].object_id == to_object_id(&obj2) or windows[1].object_id == to_object_id(&obj2));
    };

    "fetch_properties returns property map"_test = [&] {
        QtProbeHandler handler{tracker};
        auto id = to_object_id(&obj);

        std::vector<std::string> props = {"objectName"};
        auto [result] = stdexec::sync_wait(handler.fetch_properties(id, props)).value();
        expect(result.has_value());
        expect(result->contains("objectName"));
        expect((*result)["objectName"].allow_cast<QString>());
        expect((*result)["objectName"].cast<QString>() == "probe_obj");
    };

    "take_snapshot returns error for non-visual object"_test = [&] {
        QtProbeHandler handler{tracker};
        auto id = to_object_id(&obj);

        auto [result] = stdexec::sync_wait(handler.take_snapshot(id)).value();
        expect(!result.has_value());
    };
#endif
};
