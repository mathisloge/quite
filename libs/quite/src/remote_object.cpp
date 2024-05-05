#include "remote_object.hpp"

namespace quite
{
RemoteObject::RemoteObject(ObjectId id)
{}

RemoteObject::~RemoteObject() = default;

exec::task<value_handle> RemoteObject::getProperty(std::string_view property_name)
{
    co_return value_handle{};
}

} // namespace quite
