#pragma once
#include "quite/async_result.hpp"
#include "quite/remote_object.hpp"
#include "quitelib_export.h"

namespace quite::testing
{

QUITELIB_EXPORT AsyncResult<bool> create_verification_point(RemoteObjectPtr object, const std::string &name);
QUITELIB_EXPORT AsyncResult<bool> verify_verification_point(RemoteObjectPtr object, const std::string &name);

} // namespace quite::testing
