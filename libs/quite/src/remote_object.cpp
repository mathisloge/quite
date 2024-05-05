#include "remote_object.hpp"
#include "rpc/make_get_object_property_request.hpp"

namespace quite
{
RemoteObject::RemoteObject(const std::shared_ptr<ObjectClient> &api_handle, ObjectId id, std::string_view type_name)
    : api_handle_{api_handle}
    , id_{id}
    , type_name_{type_name}
{}

RemoteObject::~RemoteObject() = default;

exec::task<value_handle> RemoteObject::get_property(std::string_view property_name)
{
    const auto response =
        co_await make_get_object_property_request(api_handle_->context(), api_handle_->stub(), id_, property_name);
    co_return value_handle{.value = response->value()};
}

} // namespace quite
