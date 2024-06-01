#pragma once
#include <cstdint>
#include <expected>
#include <exec/task.hpp>
#include "async_result.hpp"
#include "image.hpp"
#include "quitelib_export.h"
#include "property.hpp"
namespace quite
{

using ObjectId = std::uint64_t;

class QUITELIB_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(ObjectId id);
    virtual ~RemoteObject();

    virtual AsyncResult<std::unordered_map<std::string, std::shared_ptr<Property>>> fetch_properties(
        const std::vector<std::string_view> &properties) = 0;

    virtual AsyncResult<std::shared_ptr<Property>> property(std::string property_name) = 0;

    virtual AsyncResult<void> mouse_action() = 0;

    virtual AsyncResult<Image> take_snapshot() = 0;

  protected:
    const ObjectId id_;
};
} // namespace quite
