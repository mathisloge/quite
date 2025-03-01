#include "context.hpp"
#include <agrpc/asio_grpc.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{

Context::Context()
{
    auto &asio_context = entt::locator<asio2exec::asio_context>::emplace();
    entt::locator<ValueRegistry>::emplace();
    asio_context.start();
    client_ = std::make_unique<proto::Client>(entt::locator<ValueRegistry>::handle(),
                                              entt::locator<asio2exec::asio_context>::handle());
}

Context::~Context()
{
    entt::locator<asio2exec::asio_context>::value().stop();
}

proto::Client &Context::backend_client()
{
    return *client_;
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
