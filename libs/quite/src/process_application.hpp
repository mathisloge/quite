#pragma once
#include <array>
#include <asio/readable_pipe.hpp>
#include "context.hpp"
#include "process.hpp"
#include "quite/application.hpp"
#include "api_handle.hpp"

namespace quite
{
class ProcessApplication final : public Application
{
  public:
    explicit ProcessApplication(Context &context, const std::string &path_to_application);
    ~ProcessApplication() override;

    std::shared_ptr<ApiHandle> api_handle() const override;

  private:
    void do_read();

  private:
    Process process_;
    asio::readable_pipe stdout_pipe_;
    asio::readable_pipe stderr_pipe_;
    std::shared_ptr<ApiHandle> api_handle_;

    std::array<char, 1024> buffer;
};
} // namespace quite
