#include "quite/quite.hpp"
#include "context.hpp"

namespace quite
{
execpools::asio_thread_pool &asio_context()
{
    return Context::Instance().asio_context();
}
} // namespace quite
