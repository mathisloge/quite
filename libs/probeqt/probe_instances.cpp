#include "probe_instances.hpp"
#include <entt/locator/locator.hpp>
#include <quite/meta/meta_registry.hpp>
#include <quite/proto/probe/dependencies.hpp>
#include <quite/proto/probe/probe_handler.hpp>
#include <quite/value/value_registry.hpp>
#include "injector/mouse_injector.hpp"
#include "qt_meta_registry.hpp"
#include "qt_probe_handler.hpp"

namespace quite::probe
{
ProbeInstances::ProbeInstances(const ObjectTracker &object_tracker)
{
    entt::locator<ValueRegistry>::emplace();
    entt::locator<proto::IProbeHandler>::emplace<QtProbeHandler>(object_tracker);
    entt::locator<meta::MetaRegistry>::emplace<QtMetaRegistry>();
    entt::locator<core::IMouseInjector>::emplace<MouseInjector>(object_tracker);

    proto::setup_dependencies(entt::locator<ValueRegistry>::handle(),
                              entt::locator<proto::IProbeHandler>::handle(),
                              entt::locator<core::IMouseInjector>::handle(),
                              entt::locator<meta::MetaRegistry>::handle());
}
} // namespace quite::probe
