#pragma once
#include <boost/asio/readable_pipe.hpp>
#include <boost/process/v2.hpp>
#include "context.hpp"
#include "grpc_impl/grpc_application.hpp"
namespace quite
{
class ProcessApplication final : public GrpcApplication
{
  public:
    explicit ProcessApplication(Context &context,
                                const std::string &path_to_application,
                                const std::vector<std::string> &args,
                                const std::unordered_map<std::string, std::string> &enviroment);
    ~ProcessApplication() override;
    AsyncResult<void> exit() override;

  private:
    void do_read();

  private:
    boost::process::v2::process process_;
};
} // namespace quite
