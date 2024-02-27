#pragma once
#include <memory>
#include "quitelib_export.h"
#include <asio/io_context.hpp>
namespace quite
{
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();

  public:
    static std::shared_ptr<Application> createApplication( asio::io_context& io_context, const std::string &path_to_application);
};
} // namespace quite
