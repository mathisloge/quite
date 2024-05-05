#pragma once
#include <array>
#include <expected>
#include <asio/readable_pipe.hpp>
#include "context.hpp"
#include "object_client.hpp"
#include "process.hpp"
#include "quite/application.hpp"
#include "quite/errors.hpp"

namespace quite
{
class ProcessApplication final : public Application
{
  public:
    explicit ProcessApplication(Context &context, const std::string &path_to_application);
    ~ProcessApplication() override;

    asio::awaitable<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> find_object(
        std::string_view object_name) override;

  private:
    void do_read();

  private:
    Process process_;
    asio::readable_pipe stdout_pipe_;
    asio::readable_pipe stderr_pipe_;
    ObjectClient object_client_;

    std::array<char, 1024> buffer;
};
} // namespace quite
