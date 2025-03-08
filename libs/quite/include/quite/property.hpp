#pragma once
#include <string>
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include <quite/async_result.hpp>
#include <quite/meta/meta_type_id.hpp>
#include "quite/quite_client_export.hpp"

namespace quite
{
class QUITE_CLIENT_EXPORT Property
{
  public:
    virtual ~Property();
    virtual const std::string &name() const = 0;
    virtual meta::TypeId type_id() const = 0;
    virtual const Result<entt::meta_any> &value() const = 0;
    virtual AsyncResult<entt::meta_any> read() = 0;
    virtual AsyncResult<entt::meta_any> write(entt::meta_any value) = 0;
};

using PropertyPtr = std::shared_ptr<Property>;
} // namespace quite
