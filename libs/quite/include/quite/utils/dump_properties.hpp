#pragma once
#include <nlohmann/json_fwd.hpp>
#include "quite/remote_object.hpp"
#include "quitelib_export.h"
namespace quite
{
AsyncResult<nlohmann::json> QUITELIB_EXPORT dump_properties(const RemoteObjectPtr &remote_object,
                                                            std::span<const std::string> properties);
}
