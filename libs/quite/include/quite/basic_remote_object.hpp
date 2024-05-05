#pragma once
#include <cstdint>
#include <string_view>
#include "quitelib_export.h"
#include <exec/task.hpp>
namespace quite
{

using ObjectId = std::uint64_t;
struct value_handle
{}; // some kind of any datatype

class QUITELIB_EXPORT BasicRemoteObject
{
  public:
    virtual ~BasicRemoteObject() = default;

    virtual exec::task<value_handle> getProperty(std::string_view property_name) = 0; // könnte awaitable sein

    // muss ein template mit beliebigen argumenten sein.
    // value_handle setProperty(std::string_view property_name, value_handle property_value);

    // muss ein template mit beliebigen argumenten sein.
    // value_handle invoke(std::string_view method_name);
};
} // namespace quite
