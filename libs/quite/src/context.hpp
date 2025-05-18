#pragma once
#include <boost/asio/io_context.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/proto/client/client.hpp>

namespace quite
{
class Context final
{
  public:
    ~Context();
    execpools::asio_thread_pool &asio_context();
    proto::Client &backend_client();

  public:
    static Context &Instance();

  private:
    Context();

  private:
    std::unique_ptr<proto::Client> client_;
};
} // namespace quite
