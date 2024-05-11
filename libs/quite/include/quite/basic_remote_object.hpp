#pragma once
#include <cstdint>
#include <string_view>
#include <exec/task.hpp>
#include "api_handle_fwd.hpp"
#include "quitelib_export.h"
namespace quite
{

using ObjectId = std::uint64_t;
struct value_handle
{
    std::string value;
}; // some kind of any datatype

class QUITELIB_EXPORT BasicRemoteObject
{
  public:
    virtual ~BasicRemoteObject() = default;

    virtual ObjectId id() const noexcept = 0;

    virtual std::shared_ptr<ApiHandle> api_handle() const = 0;

    virtual exec::task<void> mouse_click() = 0;

    virtual exec::task<void> take_snapshot() = 0;

    // muss ein template mit beliebigen argumenten sein.
    // value_handle setProperty(std::string_view property_name, value_handle property_value);

    // muss ein template mit beliebigen argumenten sein.
    // value_handle invoke(std::string_view method_name);
};
} // namespace quite
