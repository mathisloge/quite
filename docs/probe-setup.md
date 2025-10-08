# Probe setup

Currently only a compile time link setup is supported.
However in the future a `LD_PRELOAD` step is supported.
See [#51](https://github.com/mathisloge/quite/issues/51).

## C++

```cmake

find_package(quite CONFIG REQUIRED)

add_executable(myApp)

target_link_libraries(myApp PRIVATE
    quite::probe_qt
)
```

```cpp
#include <quite/probe_qt/probe_qt.hpp>

int main()
{
    auto& probe = quite::probe::setup_qt_probe(quite::GrpcServer{.server_address = "unix:///tmp/grpc_probe.sock"});

    // normal application setup
    // no more to do
}

```
