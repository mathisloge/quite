#pragma once
#include <quite/disable_copy_move.hpp>
#include <quite/error.hpp>
#include <quite/meta/meta_registry.hpp>
#include <quite/value/object_query.hpp>
#include "quite/quite_client_export.hpp"
#include "remote_object.hpp"
namespace quite::client
{
class QUITE_CLIENT_EXPORT Probe
{
  public:
    QUITE_DISABLE_COPY_MOVE(Probe);
    Probe() = default;
    virtual ~Probe() = default;
    virtual AsyncResult<RemoteObjectPtr> find_object(ObjectQuery query) = 0;
    virtual AsyncResult<std::vector<RemoteObjectPtr>> get_views() = 0;
    virtual AsyncResult<void> wait_for_started(std::chrono::seconds timeout) = 0;
    virtual AsyncResult<void> exit() = 0;
    virtual meta::MetaRegistry &meta_registry() = 0;
};
} // namespace quite::client
