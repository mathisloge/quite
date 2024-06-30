#include <quite/remote_object.hpp>
namespace quite
{
RemoteObject::RemoteObject(ObjectId id)
    : id_{id}
{}

RemoteObject::~RemoteObject() = default;

ObjectId RemoteObject::id() const noexcept
{
    return id_;
}
} // namespace quite
