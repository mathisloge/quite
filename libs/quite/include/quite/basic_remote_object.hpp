#pragma once
#include <string>

namespace quite
{
struct value_handle
{}; // some kind of any datatype
class BasicRemoteObject
{
  public:
    const std::string &getObjectName();

    value_handle getProperty(std::string_view property_name); // könnte awaitable sein
    value_handle setProperty(std::string_view property_name, value_handle property_value);
    value_handle invokeMethod(std::string_view property_name);
};
} // namespace quite
