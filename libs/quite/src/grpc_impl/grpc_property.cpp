#include "grpc_property.hpp"
namespace quite::grpc_impl
{
GrpcProperty::GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name)
    : parent_{parent}
    , name_{name}
{}

AsyncResult<Property::Value> GrpcProperty::read()
{
    co_return {};
}

AsyncResult<bool> GrpcProperty::write(const Value &value)
{
    co_return {};
}


} // namespace quite::grpc_impl
