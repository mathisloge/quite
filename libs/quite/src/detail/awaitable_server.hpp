#pragma once
#include <agrpc/server_rpc.hpp>
#include <asio/use_awaitable.hpp>

namespace quite
{
template <auto RequestRPC>
using awaitable_server_t = asio::use_awaitable_t<>::as_default_on_t<agrpc::ServerRPC<RequestRPC>>;
}
