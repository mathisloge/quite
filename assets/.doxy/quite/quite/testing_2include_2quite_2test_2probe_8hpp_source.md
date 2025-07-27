

# File probe.hpp

[**File List**](files.md) **>** [**include**](dir_0e3ab90749f7b4be0e4eb22d010aec3d.md) **>** [**quite**](dir_4b2197acd3cfc200796c46ec50ed103f.md) **>** [**test**](dir_e2259a6ae36431ad829e5c40f57eb4d8.md) **>** [**probe.hpp**](testing_2include_2quite_2test_2probe_8hpp.md)

[Go to the documentation of this file](testing_2include_2quite_2test_2probe_8hpp.md)


```C++
#pragma once
#include <chrono>
#include <memory>
#include <quite/client/probe_handle.hpp>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_test_export.hpp"
#include "remote_object.hpp"

namespace quite
{
class ObjectQuery;

namespace test
{
class ProbeManager;
class QUITE_TEST_EXPORT Probe
{
  public:
    QUITE_DISABLE_COPY(Probe);
    Probe(Probe &&) noexcept;
    Probe &operator=(Probe &&) noexcept;
    ~Probe();

    RemoteObject find_object(ObjectQuery query);
    RemoteObject try_find_object(ObjectQuery query, std::chrono::milliseconds timeout);
    void wait_for_connected(std::chrono::seconds timeout);
    void exit();

  private:
    friend ProbeManager;
    explicit Probe(client::ProbeHandle handle);

  private:
    client::ProbeHandle handle_;
};
} // namespace test
} // namespace quite
```


