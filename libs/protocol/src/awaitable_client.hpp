#pragma once

#include <agrpc/client_rpc.hpp>
#include <asio/use_awaitable.hpp>

namespace quite
{
template <auto PrepareAsync>
using awaitable_client_t = asio::use_awaitable_t<>::as_default_on_t<agrpc::ClientRPC<PrepareAsync>>;
}
