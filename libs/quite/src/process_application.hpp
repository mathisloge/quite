#pragma once
#include <array>
#include <asio/readable_pipe.hpp>
#include "context.hpp"
#include "grpc_impl/probe_handle.hpp"
#include "process.hpp"
#include "quite/application.hpp"

namespace quite
{
class ProcessApplication final : public Application
{
  public:
    explicit ProcessApplication(Context &context, const std::string &path_to_application);
    ~ProcessApplication() override;

    AsyncResult<std::shared_ptr<RemoteObject>> find_object(std::string_view object_name) override;
    AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> get_views() override;

  private:
    void do_read();

  private:
    Process process_;
    asio::readable_pipe stdout_pipe_;
    asio::readable_pipe stderr_pipe_;

    std::array<char, 1024> buffer;

    grpc_impl::ProbeServiceHandle probe_handle_;
};
} // namespace quite
