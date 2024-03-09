#pragma once
#include <quite/basic_object_client.hpp>
#include <quite/basic_remote_object.hpp>
namespace quite
{
class ObjectClient final : public BasicObjectClient
{
  public:
    using BasicObjectClient::BasicObjectClient;

    asio::awaitable<std::string> sayHello(const std::string &name);
    asio::awaitable<void> findObject();
};
} // namespace quite
