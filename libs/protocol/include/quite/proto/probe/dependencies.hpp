#pragma once
#include <entt/locator/locator.hpp>
#include "quite/quite_protocol_export.hpp"

namespace quite
{
class ValueRegistry;
namespace core
{
class IMouseInjector;
}
namespace meta
{
class MetaRegistry;
}
} // namespace quite
namespace quite::proto
{
class IObjectHandler;
/**
 * @brief Needed to be called if the protocol lib is used as a shared library.
 */
QUITE_PROTOCOL_EXPORT void setup_dependencies(entt::locator<ValueRegistry>::node_type value_registry,
                                              entt::locator<IObjectHandler>::node_type object_handler,
                                              entt::locator<core::IMouseInjector>::node_type mouse_injector,
                                              entt::locator<meta::MetaRegistry>::node_type meta_registry);
} // namespace quite::proto
