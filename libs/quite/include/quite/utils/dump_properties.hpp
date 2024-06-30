#pragma once
#include <nlohmann/json_fwd.hpp>
#include "quite/remote_object.hpp"
namespace quite
{
AsyncResult<nlohmann::json> dump_properties(const RemoteObjectPtr &remote_object,
                                  const std::vector<std::string_view> &properties);
}
