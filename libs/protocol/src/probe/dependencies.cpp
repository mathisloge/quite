#include "quite/proto/probe/dependencies.hpp"

namespace quite::proto
{
void setup_dependencies(entt::locator<ValueRegistry>::node_type value_registry,
                        entt::locator<IProbeHandler>::node_type object_handler,
                        entt::locator<core::IMouseInjector>::node_type mouse_injector,
                        entt::locator<meta::MetaRegistry>::node_type meta_registry)
{
    entt::locator<ValueRegistry>::reset(std::move(value_registry));
    entt::locator<IProbeHandler>::reset(std::move(object_handler));
    entt::locator<core::IMouseInjector>::reset(std::move(mouse_injector));
    entt::locator<meta::MetaRegistry>::reset(std::move(meta_registry));
}
} // namespace quite::proto
