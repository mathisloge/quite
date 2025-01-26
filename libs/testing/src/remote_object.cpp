#include "quite/test/remote_object.hpp"

namespace quite::test
{

RemoteObject::RemoteObject(std::shared_ptr<quite::RemoteObject> object)
    : object_{std::move(object)}
{}
} // namespace quite::test
