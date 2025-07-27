

# File probe\_manager.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**probe\_manager.cpp**](testing_2src_2probe__manager_8cpp.md)

[Go to the documentation of this file](testing_2src_2probe__manager_8cpp.md)


```C++
#include "quite/test/probe_manager.hpp"
#include <quite/asio_context.hpp>
#include <quite/client/probe_manager.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/setup_logger.hpp>
#include "quite/test/probe.hpp"

namespace quite::test
{
ProbeManager::ProbeManager()
    : local_{std::make_unique<manager::ProcessManager>(quite::get_executor())}
    , probe_{std::make_unique<client::ProbeManager>()}
{}

ProbeManager::~ProbeManager() = default;

Probe ProbeManager::launch_probe_application(std::string name,
                                             const std::string &path_to_application,
                                             const std::vector<std::string> &args)
{
    auto [process] =
        stdexec::sync_wait(local_->launch_application({std::move(name)}, path_to_application, args)).value();
    auto probe_result = process.and_then([&](auto &&handle) -> Result<Probe> {
        auto probe_handle = probe_->connect(std::forward<decltype(handle)>(handle), "unix:///tmp/grpc_probe.sock");
        return Probe{std::move(probe_handle)};
    });
    if (probe_result.has_value())
    {
        return std::move(probe_result.value());
    }
    return Probe{probe_->connect(local_->noop_process(), "unknown")};
}

quite::test::Probe ProbeManager::connect_to_probe(std::string name)
{
    auto probe_handle = probe_->connect(local_->noop_process(), "unix:///tmp/grpc_probe.sock");
    return Probe{std::move(probe_handle)};
}
} // namespace quite::test
```


