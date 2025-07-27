

# File test\_server.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**tests**](dir_0600a918fa506c296d39916ce5da6191.md) **>** [**test\_server.cpp**](test__server_8cpp.md)

[Go to the documentation of this file](test__server_8cpp.md)


```C++
#include <thread>
#include <boost/ut.hpp>
#include <quite/proto/probe/server.hpp>
using namespace boost::ut;
using namespace std::literals::string_view_literals;

static suite<"protocol server"> _ = [] { // NOLINT
    "shutdown instant"_test = [] {
        // This test is to ensure that the server can be created and destroyed without issues.
        for (int i = 0; i < 1000; ++i)
        {
            quite::proto::Server server{"unix:///tmp/grpc_probe.sock", {}, {}, {}, {}};
        }
    };
    "shutdown delayed"_test = [] {
        quite::proto::Server server{"unix:///tmp/grpc_probe.sock", {}, {}, {}, {}};
        std::this_thread::sleep_for(std::chrono::seconds(1));
    };
};
```


