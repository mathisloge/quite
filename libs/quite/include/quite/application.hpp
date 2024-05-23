#pragma once
#include <memory>
#include "errors.hpp"
#include "quitelib_export.h"
#include "remote_object.hpp"
namespace quite
{
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();
    virtual exec::task<Result<std::shared_ptr<RemoteObject>>> find_object(std::string_view object_name) = 0;

  protected:
    Application();

  public:
    static std::shared_ptr<Application> CreateApplication(const std::string &path_to_application);
};
} // namespace quite
