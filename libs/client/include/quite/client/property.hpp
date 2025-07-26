#pragma once
#include <string>
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include <quite/async_result.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/meta/meta_type_id.hpp>
#include "quite/quite_client_export.hpp"

namespace quite::client
{
class QUITE_CLIENT_EXPORT Property
{
  public:
    QUITE_DISABLE_COPY_MOVE(Property);
    Property() = default;
    virtual ~Property();
    virtual const std::string &name() const = 0;
    virtual meta::TypeId type_id() const = 0;
    virtual const Result<entt::meta_any> &value() const = 0;
    virtual AsyncResult<entt::meta_any> read() = 0;
    virtual AsyncResult<void> write(entt::meta_any value) = 0;
};

using PropertyPtr = std::shared_ptr<Property>;
} // namespace quite::client
