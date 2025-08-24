// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/probe_qt/probe_qt.hpp"
#include <quite/setup_logger.hpp>
#include <quite/value/value_registry.hpp>
#include "probe_context.hpp"
#include "quite/probe.hpp"

namespace quite::probe
{
Probe &setup_qt_probe(GrpcServer server_config)
{
    setup_logger(false);
    return entt::locator<probe::ProbeContext>::emplace(server_config.server_address);
}
} // namespace quite::probe
