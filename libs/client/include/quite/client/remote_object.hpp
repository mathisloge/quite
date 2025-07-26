#pragma once
#include <cstdint>
#include <exec/task.hpp>
#include <quite/async_result.hpp>
#include "property.hpp"
#include "quite/image.hpp"
#include "quite/quite_client_export.hpp"
namespace quite::client
{

using ObjectId = std::uint64_t;

class QUITE_CLIENT_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(ObjectId id);
    virtual ~RemoteObject();

    ObjectId id() const noexcept;

    virtual meta::TypeId type_id() const = 0;

    virtual AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        std::vector<std::string> properties) = 0;

    virtual AsyncResult<PropertyPtr> property(std::string property_name) = 0;

    virtual AsyncResult<void> write_property(std::string property_name, entt::meta_any value) = 0;

    virtual AsyncResult<void> mouse_action() = 0;

    virtual AsyncResult<Image> take_snapshot() = 0;

    virtual AsyncResult<void> invoke_method(std::string method_name) = 0;

  private:
    const ObjectId id_;
};
using RemoteObjectPtr = std::shared_ptr<RemoteObject>;
} // namespace quite::client
