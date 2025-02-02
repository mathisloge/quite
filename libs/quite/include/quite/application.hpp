#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/error.hpp>
#include <quite/meta/meta_registry.hpp>
#include "object_query.hpp"
#include "quite/quite_client_export.hpp"
#include "remote_object.hpp"
namespace quite
{
class QUITE_CLIENT_EXPORT Application
{
  public:
    QUITE_DISABLE_COPY_MOVE(Application);
    virtual ~Application();
    virtual AsyncResult<RemoteObjectPtr> find_object(const ObjectQuery &query) = 0;
    virtual AsyncResult<std::vector<RemoteObjectPtr>> get_views() = 0;
    virtual AsyncResult<void> exit() = 0;
    virtual meta::MetaRegistry &meta_registry() = 0;

  protected:
    Application();
};
} // namespace quite
