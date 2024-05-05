#pragma once
#include <expected>
#include <memory>
#include <asio/awaitable.hpp>
#include "basic_remote_object.hpp"
#include "errors.hpp"
#include "quitelib_export.h"
namespace quite
{
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();
    virtual asio::awaitable<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> find_object(
        std::string_view object_name) = 0;

  protected:
    Application();

  public:
    static std::shared_ptr<Application> CreateApplication(const std::string &path_to_application);
};
} // namespace quite
