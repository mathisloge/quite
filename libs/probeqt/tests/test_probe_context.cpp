#include <QObject>
#include <memory>
#include <boost/ut.hpp>
#include "probe_context.hpp"

using namespace boost::ut;
using quite::probe::ProbeContext;

suite<"qtprobe ProbeContext"> _ = [] { // NOLINT
    "ProbeContext can be constructed and destructed"_test = [] {
        // Should not crash or throw
        ProbeContext ctx{"localhost:12345"};
    };

    "ProbeContext installs and restores Qt hooks"_test = [] {
        // Check if hooks are restored on destruction
        {
            ProbeContext ctx{"localhost:12345"};
            expect(qtHookData[QHooks::AddQObject] != 0);
            expect(qtHookData[QHooks::RemoveQObject] != 0);
            expect(qtHookData[QHooks::Startup] != 0);
        }
        expect(qtHookData[QHooks::AddQObject] == 0);
        expect(qtHookData[QHooks::RemoveQObject] == 0);
        expect(qtHookData[QHooks::Startup] == 0);
    };
};
