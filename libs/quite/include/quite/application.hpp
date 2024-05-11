#pragma once
#include <memory>
#include "api_handle_fwd.hpp"
#include "quitelib_export.h"
namespace quite
{
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();

    virtual std::shared_ptr<ApiHandle> api_handle() const = 0;

  protected:
    Application();

  public:
    static std::shared_ptr<Application> CreateApplication(const std::string &path_to_application);
};
} // namespace quite
