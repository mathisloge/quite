#pragma once
#include <quite/proto/client/probe_client.hpp>
#include "quite/value.hpp"
namespace quite
{
quite::Result<quite::Value> convert(const entt::meta_any &value, std::shared_ptr<proto::ProbeClient> client);
}
