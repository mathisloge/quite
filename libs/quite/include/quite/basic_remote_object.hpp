#pragma once
#include <string>
#include "quitelib_export.h"
namespace quite
{
struct value_handle
{}; // some kind of any datatype

/**
at 
*/
class QUITELIB_EXPORT BasicRemoteObject
{
  public:
    virtual ~BasicRemoteObject() = default;

    const std::string &getObjectName();

    value_handle getProperty(std::string_view property_name); // könnte awaitable sein

    // muss ein template mit beliebigen argumenten sein.
    value_handle setProperty(std::string_view property_name, value_handle property_value);

    // muss ein template mit beliebigen argumenten sein.
    value_handle invoke(std::string_view method_name);
};
} // namespace quite
