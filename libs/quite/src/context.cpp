#include "context.hpp"
#include <agrpc/asio_grpc.hpp>
#include <quite/proto/client/dependencies.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{

Context::Context()
{
    auto &asio_context = entt::locator<asio2exec::asio_context>::emplace();
    entt::locator<ValueRegistry>::emplace();
    proto::setup_dependencies(entt::locator<ValueRegistry>::handle(), entt::locator<asio2exec::asio_context>::handle());
    asio_context.start();
}

Context::~Context()
{
    entt::locator<asio2exec::asio_context>::value().stop();
}

asio2exec::asio_context &Context::asio_context()
{
    return entt::locator<asio2exec::asio_context>::value();
}

Context &Context::Instance()
{
    static Context context;
    return context;
}
} // namespace quite
