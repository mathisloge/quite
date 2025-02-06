#pragma once
#include <nlohmann/json_fwd.hpp>
#include "quite/quite_client_export.hpp"
#include "quite/remote_object.hpp"
namespace quite
{
AsyncResult<nlohmann::json> QUITE_CLIENT_EXPORT dump_properties(const RemoteObjectPtr &remote_object,
                                                                std::span<const std::string> properties);
}
