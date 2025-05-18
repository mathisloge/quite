#pragma once
#include <memory>
#include "quite/quite_client_export.hpp"
namespace quite::client
{
class Probe;
class QUITE_CLIENT_EXPORT ProbeHandle
{
  public:
    explicit ProbeHandle(std::shared_ptr<Probe> probe);
    Probe *operator->();

  private:
    std::shared_ptr<Probe> probe_;
};
} // namespace quite::client
