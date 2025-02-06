#include "quite/test/remote_object.hpp"
#include <quite/remote_object.hpp>
namespace quite::test
{

RemoteObject::RemoteObject(std::shared_ptr<quite::RemoteObject> object)
    : object_{std::move(object)}
{}

void RemoteObject::mouse_action()
{
    stdexec::sync_wait(object_->mouse_action());
}

void RemoteObject::take_snapshot()
{
    auto result = stdexec::sync_wait(object_->take_snapshot());
    auto &&[snapshot] = result.value();
    if (snapshot.has_value())
    {
        snapshot->save_to("test.png");
    }
}
} // namespace quite::test
