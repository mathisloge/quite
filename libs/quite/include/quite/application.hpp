#pragma once
#include <memory>
#include <asio/awaitable.hpp>
#include "quitelib_export.h"
namespace quite
{
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();
    virtual asio::awaitable<void> test() = 0;

  protected:
    Application();

  public:
    static std::shared_ptr<Application> CreateApplication(const std::string &path_to_application);
};
} // namespace quite
