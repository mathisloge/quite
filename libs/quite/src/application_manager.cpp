#include "quite/application_manager.hpp"
#include "context.hpp"
#include "process_application.hpp"

namespace quite
{
struct ApplicationManager::Impl
{};

ApplicationManager::ApplicationManager()
    : impl_{std::make_unique<Impl>()}
{}

ApplicationManager::~ApplicationManager()
{}

ApplicationPtr ApplicationManager::create_host_application(
    const std::string &path_to_application,
    const std::vector<std::string> &args,
    const std::unordered_map<std::string, std::string> &environment)
{
    return std::make_shared<ProcessApplication>(Context::Instance(), path_to_application, args, environment);
}

ApplicationPtr ApplicationManager::attach_to_running([[maybe_unused]] const std::string &connection_url)
{
    return std::make_shared<grpc_impl::GrpcApplication>(Context::Instance());
}
} // namespace quite
