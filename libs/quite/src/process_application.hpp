#pragma once
#include "quite/application.hpp"

namespace uvw
{
class process_handle;
class pipe_handle;
} // namespace uvw

namespace quite
{
class ProcessApplication final : public Application
{
  public:
    explicit ProcessApplication(const std::string &path_to_application);
    ~ProcessApplication() override;

  private:
    std::shared_ptr<uvw::process_handle> process_;
    std::shared_ptr<uvw::pipe_handle> out_pipe_;
};
} // namespace quite
