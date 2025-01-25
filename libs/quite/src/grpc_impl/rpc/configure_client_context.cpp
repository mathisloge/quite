#include "configure_client_context.hpp"

namespace quite::grpc_impl
{
void configure_client_context(grpc::ClientContext &client_context)
{
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{5});
    client_context.set_wait_for_ready(true);
}
} // namespace quite::grpc_impl