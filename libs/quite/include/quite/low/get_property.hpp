#pragma once
#include <expected>
#include <quite/basic_remote_object.hpp>
#include <quite/errors.hpp>
#include "quitelib_export.h"

namespace quite
{
class Application;
}
namespace quite::low
{
QUITELIB_EXPORT exec::task<std::expected<value_handle, FindObjectErrorCode>> get_property(
    const BasicRemoteObject &obj, std::string_view property_name);
} // namespace quite::low
