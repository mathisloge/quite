#include "configure_client_context.hpp"

namespace quite::proto
{
void configure_client_context(grpc::ClientContext &client_context)
{
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{10});
    client_context.set_wait_for_ready(true);
}
} // namespace quite::proto
