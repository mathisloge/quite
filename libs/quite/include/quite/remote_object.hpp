#pragma once
#include <cstdint>
#include <exec/task.hpp>
#include <quite/async_result.hpp>
#include "image.hpp"
#include "property.hpp"
#include "quitelib_export.h"
namespace quite
{

using ObjectId = std::uint64_t;

class QUITELIB_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(ObjectId id);
    virtual ~RemoteObject();

    ObjectId id() const noexcept;

    virtual AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        const std::vector<std::string_view> &properties) = 0;

    virtual AsyncResult<PropertyPtr> property(std::string property_name) = 0;

    virtual AsyncResult<void> mouse_action() = 0;

    virtual AsyncResult<Image> take_snapshot() = 0;

  private:
    const ObjectId id_;
};
using RemoteObjectPtr = std::shared_ptr<RemoteObject>;
} // namespace quite
