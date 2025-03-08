#pragma once
#include <boost/asio/io_context.hpp>
#include <quite/asio2exec.hpp>
#include <quite/proto/client/client.hpp>

namespace quite
{
class Context final
{
  public:
    ~Context();
    asio2exec::asio_context &asio_context();
    proto::Client &backend_client();

  public:
    static Context &Instance();

  private:
    Context();

  private:
    std::unique_ptr<proto::Client> client_;
};
} // namespace quite
