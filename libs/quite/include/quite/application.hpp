#pragma once
#include <memory>
#include <quite/error.hpp>
#include <quite/meta/meta_registry.hpp>
#include "object_query.hpp"
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
    virtual AsyncResult<RemoteObjectPtr> find_object(const ObjectQuery &query) = 0;
    virtual AsyncResult<std::vector<RemoteObjectPtr>> get_views() = 0;
    virtual AsyncResult<void> exit() = 0;
    virtual meta::MetaRegistry &meta_registry() = 0;

  protected:
    Application();

  public:
    static ApplicationPtr CreateApplication(const std::string &path_to_application);
};
} // namespace quite
