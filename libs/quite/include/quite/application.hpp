#pragma once
#include <memory>
#include "async_result.hpp"
#include "quitelib_export.h"
#include "remote_object.hpp"
namespace quite
{

class Application;
using ApplicationPtr = std::shared_ptr<Application>;
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();
    virtual AsyncResult<RemoteObjectPtr> find_object(std::string_view object_name) = 0;
    virtual AsyncResult<std::vector<RemoteObjectPtr>> get_views() = 0;

  protected:
    Application();

  public:
    static ApplicationPtr CreateApplication(const std::string &path_to_application);
};
} // namespace quite
