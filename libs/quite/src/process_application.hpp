#pragma once
#include <array>
#include <asio/readable_pipe.hpp>
#include "context.hpp"
#include "grpc_impl/grpc_application.hpp"
#include "process.hpp"
namespace quite
{
class ProcessApplication final : public grpc_impl::GrpcApplication
{
  public:
    explicit ProcessApplication(Context &context, const std::string &path_to_application);
    ~ProcessApplication() override;

  private:
    void do_read();

  private:
    Process process_;
    asio::readable_pipe stdout_pipe_;
    asio::readable_pipe stderr_pipe_;

    std::array<char, 1024> buffer;
};
} // namespace quite
