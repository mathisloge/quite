#include "quite/quite.hpp"
#include "context.hpp"

namespace quite
{
asio::any_io_executor globalExecutor()
{
    return Context::Instance().asioContext().get_executor().get_executor();
}
} // namespace quite
