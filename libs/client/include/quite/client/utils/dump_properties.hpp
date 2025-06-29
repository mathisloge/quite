#pragma once
#include <nlohmann/json_fwd.hpp>
#include "quite/client/remote_object.hpp"
#include "quite/quite_client_export.hpp"
namespace quite::client
{
AsyncResult<nlohmann::json> QUITE_CLIENT_EXPORT dump_properties(RemoteObjectPtr remote_object,
                                                                std::vector<std::string> properties);
}
