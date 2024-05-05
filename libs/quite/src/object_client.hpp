#pragma once
#include <expected>
#include <quite/basic_remote_object.hpp>
#include "basic_object_client.hpp"
#include "quite/errors.hpp"
namespace quite
{
class ObjectClient final : public BasicObjectClient
{
  public:
    using BasicObjectClient::BasicObjectClient;

    asio::awaitable<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> findObject();
};
} // namespace quite
