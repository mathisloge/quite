#include "quite/quite.hpp"
#include "context.hpp"

namespace quite
{
asio2exec::asio_context &asio_context()
{
    return Context::Instance().asio_context();
}
} // namespace quite
