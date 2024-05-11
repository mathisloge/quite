#pragma once
#include <memory>
#include "object_client.hpp"
namespace quite
{
class ApiHandle final : public std::enable_shared_from_this<ApiHandle>
{
  public:
    ApiHandle(agrpc::GrpcContext &grpc_context);
    ~ApiHandle();

    ObjectClient &object_client();

  private:
    ObjectClient object_client_;
};
} // namespace quite
