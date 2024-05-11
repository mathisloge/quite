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
QUITELIB_EXPORT exec::task<std::expected<std::shared_ptr<BasicRemoteObject>, FindObjectErrorCode>> find_object(
    const Application &app, std::string_view object_name);
} // namespace quite::low
