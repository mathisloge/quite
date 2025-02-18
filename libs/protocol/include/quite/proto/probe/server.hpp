#pragma once
#include <memory>
#include <string>
#include <entt/locator/locator.hpp>
#include <quite/disable_copy_move.hpp>
namespace quite::proto
{
class ObjectHandler;

class Server final
{
  public:
    QUITE_DISABLE_COPY(Server);
    Server(std::string server_address, entt::locator<ObjectHandler>::node_type object_handler);
    Server(Server &&server) noexcept;
    Server &operator=(Server &&server) noexcept;
    ~Server();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::proto
