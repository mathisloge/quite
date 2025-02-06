#include "quite/quite.hpp"
#include "context.hpp"

namespace quite
{
boost::asio::any_io_executor globalExecutor()
{
    return Context::Instance().asioContext().get_executor().get_executor();
}

asio2exec::asio_context &asio_context()
{
    return Context::Instance().asioContext();
}
} // namespace quite
