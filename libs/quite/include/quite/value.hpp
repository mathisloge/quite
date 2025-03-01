#pragma once
#include <cstdint>
#include <variant>
#include <entt/meta/meta.hpp>
#include "indirect.hpp"
#include "quite/quite_client_export.hpp"

namespace quite
{
class RemoteObject;

using Value = std::variant<std::int64_t,
                           std::uint64_t,
                           double,
                           bool,
                           std::string,
                           std::shared_ptr<RemoteObject>,
                           xyz::indirect<struct ArrayObject>,
                           xyz::indirect<struct ClassObject>>;

} // namespace quite
namespace quite::details
{
entt::meta_any QUITE_CLIENT_EXPORT convert(const quite::Value &value);
} // namespace quite::details
