// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "create_probe_context.hpp"
#include "probe_context.hpp"

namespace quite::probe
{
Probe &create_probe_context(GrpcServer server_config)
{
    return entt::locator<probe::ProbeContext>::emplace(server_config.server_address);
}
} // namespace quite::probe
