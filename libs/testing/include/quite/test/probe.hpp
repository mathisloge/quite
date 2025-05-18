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

    RemoteObject find_object(std::shared_ptr<ObjectQuery> query);
    RemoteObject try_find_object(std::shared_ptr<ObjectQuery> query, std::chrono::milliseconds timeout);
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
