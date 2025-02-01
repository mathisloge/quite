#pragma once
#include "quite/async_result.hpp"
#include "quite/quite_client_export.hpp"
#include "quite/remote_object.hpp"

namespace quite::testing
{

QUITE_CLIENT_EXPORT AsyncResult<bool> create_verification_point(RemoteObjectPtr object, const std::string &name);
QUITE_CLIENT_EXPORT AsyncResult<bool> verify_verification_point(RemoteObjectPtr object, const std::string &name);

} // namespace quite::testing
