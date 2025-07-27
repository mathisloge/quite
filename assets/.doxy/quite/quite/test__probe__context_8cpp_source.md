

# File test\_probe\_context.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**tests**](dir_c1613d43beada98aaa8aaa25db1fb827.md) **>** [**test\_probe\_context.cpp**](test__probe__context_8cpp.md)

[Go to the documentation of this file](test__probe__context_8cpp.md)


```C++
#include <QObject>
#include <boost/ut.hpp>
#include "probe_context.hpp"

using namespace boost::ut;
using quite::probe::ProbeContext;

static suite<"qtprobe ProbeContext"> _ = [] { // NOLINT
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
```


