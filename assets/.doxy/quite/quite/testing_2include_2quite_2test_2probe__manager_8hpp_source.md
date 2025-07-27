

# File probe\_manager.hpp

[**File List**](files.md) **>** [**include**](dir_0e3ab90749f7b4be0e4eb22d010aec3d.md) **>** [**quite**](dir_4b2197acd3cfc200796c46ec50ed103f.md) **>** [**test**](dir_e2259a6ae36431ad829e5c40f57eb4d8.md) **>** [**probe\_manager.hpp**](testing_2include_2quite_2test_2probe__manager_8hpp.md)

[Go to the documentation of this file](testing_2include_2quite_2test_2probe__manager_8hpp.md)


```C++
#pragma once
#include <memory>
#include <vector>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_test_export.hpp"

namespace quite
{
namespace client
{
class ProbeManager;
}
namespace manager
{
class ProcessManager;
}

namespace test
{
class Probe;
class QUITE_TEST_EXPORT ProbeManager
{
  public:
    QUITE_DISABLE_COPY(ProbeManager);

    ProbeManager();
    ProbeManager(ProbeManager &&) noexcept = default;
    ProbeManager &operator=(ProbeManager &&) noexcept = default;
    ~ProbeManager();
    quite::test::Probe launch_probe_application(std::string name,
                                                const std::string &path_to_application,
                                                const std::vector<std::string> &args = {});
    quite::test::Probe connect_to_probe(std::string name);

  private:
    std::unique_ptr<manager::ProcessManager> local_;
    std::unique_ptr<client::ProbeManager> probe_;
};
} // namespace test
} // namespace quite
```


