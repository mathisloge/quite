#include "quite/proto/client/dependencies.hpp"
namespace quite::proto
{
void setup_dependencies(entt::locator<ValueRegistry>::node_type value_registry,
                        entt::locator<asio2exec::asio_context>::node_type io_context)
{
    entt::locator<ValueRegistry>::reset(std::move(value_registry));
    entt::locator<asio2exec::asio_context>::reset(std::move(io_context));
}
} // namespace quite::proto
