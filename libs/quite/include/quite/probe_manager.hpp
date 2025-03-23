#pragma once
#include <memory>
#include <quite/disable_copy_move.hpp>
#include <quite/manager/process_manager.hpp>
#include "probe_handle.hpp"
#include "quite/quite_client_export.hpp"

namespace quite::client
{
class QUITE_CLIENT_EXPORT ProbeManager
{
  public:
    QUITE_DISABLE_COPY(ProbeManager);
    ProbeManager();
    ~ProbeManager();
    ProbeManager(ProbeManager &&) noexcept = default;
    ProbeManager &operator=(ProbeManager &&) noexcept = default;

    ProbeHandle connect(manager::ProcessHandle handle, const std::string &connection_url);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::client
