#pragma once
#include <memory>
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
    quite::test::Probe launch_probe_application(std::string name, const std::string &path_to_application);

  private:
    std::unique_ptr<manager::ProcessManager> local_;
    std::unique_ptr<client::ProbeManager> probe_;
};
} // namespace test
} // namespace quite
