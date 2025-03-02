#pragma once
#include <cstdint>
#include <variant>
#include <entt/meta/meta.hpp>
#include "indirect.hpp"
#include "quite/quite_client_export.hpp"

namespace quite
{
class RemoteObject;
struct ArrayObject;
struct ClassObject;

using Value = std::variant<bool,
                           std::uint64_t,
                           std::int64_t,
                           double,
                           std::string,
                           std::shared_ptr<RemoteObject>,
                           xyz::indirect<ArrayObject>,
                           xyz::indirect<ClassObject>>;

} // namespace quite
namespace quite::details
{
QUITE_CLIENT_EXPORT entt::meta_any convert(const quite::Value &value);
} // namespace quite::details
