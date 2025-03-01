#pragma once
#include <entt/locator/locator.hpp>
#include <quite/asio2exec.hpp>
#include "quite/quite_protocol_export.hpp"

namespace quite
{
class ValueRegistry;
}
namespace quite::proto
{
/**
 * @brief Needed to be called if the protocol lib is used as a shared library.
 */
QUITE_PROTOCOL_EXPORT void setup_dependencies(entt::locator<ValueRegistry>::node_type value_registry,
                                              entt::locator<asio2exec::asio_context>::node_type io_context);
} // namespace quite::proto
