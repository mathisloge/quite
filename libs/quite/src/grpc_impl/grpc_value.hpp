#include <quite/proto/types.pb.h>
#include <quite/value_handle.hpp>

namespace quite::grpc_impl
{
class GrpcValue final : public Value
{
  public:
    explicit GrpcValue(proto::Value value);

    Type value() const override;

  private:
    proto::Value value_;
};
} // namespace quite::grpc_impl
