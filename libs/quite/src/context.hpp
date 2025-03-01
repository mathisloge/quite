#pragma once
#include <boost/asio/io_context.hpp>
#include <quite/asio2exec.hpp>

namespace quite
{
class Context final
{
  public:
    ~Context();
    asio2exec::asio_context &asio_context();

  public:
    static Context &Instance();

  private:
    Context();
};
} // namespace quite
