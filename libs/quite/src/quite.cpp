#include "quite/quite.hpp"
#include "context.hpp"

namespace quite
{
asio::any_io_executor globalExecutor()
{
    return Context::Instance().ioContext().get_executor();
}
} // namespace quite
