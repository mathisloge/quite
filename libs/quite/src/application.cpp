#include "quite/application.hpp"
#include "context.hpp"
#include "grpc_impl/grpc_application.hpp"
#include "process_application.hpp"

namespace quite
{

Application::Application() = default;
Application::~Application() = default;

std::shared_ptr<Application> Application::CreateApplication(const std::string &path_to_application)
{
    if (path_to_application.empty())
    {
        return std::make_shared<grpc_impl::GrpcApplication>(Context::Instance());
    }
    return std::make_shared<ProcessApplication>(Context::Instance(), path_to_application);
}
} // namespace quite
