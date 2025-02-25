#include "probe_instances.hpp"
#include <entt/locator/locator.hpp>
#include <quite/meta/meta_registry.hpp>
#include <quite/proto/probe/dependencies.hpp>
#include <quite/proto/probe/object_handler.hpp>
#include <quite/value/value_registry.hpp>
#include "injector/mouse_injector.hpp"
#include "object_handler.hpp"
#include "qt_meta_registry.hpp"

namespace quite::probe
{
ProbeInstances::ProbeInstances(const ObjectTracker &object_tracker)
{
    entt::locator<ValueRegistry>::emplace();
    entt::locator<proto::IObjectHandler>::emplace<ObjectHandler>(object_tracker);
    entt::locator<meta::MetaRegistry>::emplace<QtMetaRegistry>();
    entt::locator<core::IMouseInjector>::emplace<MouseInjector>(object_tracker);

    proto::setup_dependencies(entt::locator<ValueRegistry>::handle(),
                              entt::locator<proto::IObjectHandler>::handle(),
                              entt::locator<core::IMouseInjector>::handle(),
                              entt::locator<meta::MetaRegistry>::handle());
}
} // namespace quite::probe
