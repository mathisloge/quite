#include "error_helper.hpp"
namespace quite::grpc_impl
{
Error status2error(const grpc::Status &status)
{
    return Error{.message = status.error_message()};
}
} // namespace quite::grpc_impl
