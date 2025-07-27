

# File grpc\_property.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**grpc\_impl**](dir_61027e8bdb8101310df75c312f0d65c4.md) **>** [**grpc\_property.cpp**](grpc__property_8cpp.md)

[Go to the documentation of this file](grpc__property_8cpp.md)


```C++
#include "grpc_property.hpp"
#include <quite/logger.hpp>

DEFINE_LOGGER(grpc_property_logger)

namespace quite::client
{
GrpcProperty::GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name, entt::meta_any initial_value)
    : parent_{std::move(parent)}
    , name_{std::move(name)}
    , last_value_{std::move(initial_value)}
    , type_id_{0} // TODO
{}

GrpcProperty::~GrpcProperty() = default;

const std::string &GrpcProperty::name() const
{
    return name_;
}

meta::TypeId GrpcProperty::type_id() const
{
    return type_id_;
}

const Result<entt::meta_any> &GrpcProperty::value() const
{
    return last_value_;
}

AsyncResult<entt::meta_any> GrpcProperty::read()
{
    LOG_DEBUG(grpc_property_logger(), "get property[{}] for object={}", name_, parent_->id());
    last_value_ = co_await parent_->fetch_property({name_});
    co_return last_value_;
}

AsyncResult<void> GrpcProperty::write(entt::meta_any value)
{
    LOG_DEBUG(grpc_property_logger(), "set property[{}] for object={}", name_, parent_->id());
    co_return co_await parent_->write_property(name_, std::move(value));
}

} // namespace quite::client
```


