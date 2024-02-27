#pragma once
#include <array>
#include <asio/readable_pipe.hpp>
#include "quite/application.hpp"

namespace quite
{
class ProcessApplication final : public Application
{
  public:
    explicit ProcessApplication(asio::io_context &io_context, const std::string &path_to_application);
    ~ProcessApplication() override;

  private:
    void do_read();

  private:
    pid_t pid_;
    std::array<int, 2> out_pipe_;
    std::array<int, 2> err_pipe_;
    asio::readable_pipe stdout_pipe_;
    asio::readable_pipe stderr_pipe_;

    std::array<char, 1024> buffer;
};
} // namespace quite
