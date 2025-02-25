#pragma once
#include <memory>
#include <string>
#include <entt/locator/locator.hpp>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_protocol_export.hpp"

namespace quite::proto
{
class IObjectHandler;

class QUITE_PROTOCOL_EXPORT Server final
{
  public:
    QUITE_DISABLE_COPY(Server);
    Server(std::string server_address);
    Server(Server &&server) noexcept;
    Server &operator=(Server &&server) noexcept;
    ~Server();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::proto
