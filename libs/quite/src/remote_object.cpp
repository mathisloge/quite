#include <quite/remote_object.hpp>
namespace quite
{
RemoteObject::RemoteObject(ObjectId id)
    : id_{id}
{}

RemoteObject::~RemoteObject() = default;
} // namespace quite
