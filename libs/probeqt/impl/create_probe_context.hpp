// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/probe.hpp>

namespace quite::probe
{
Probe &create_probe_context(GrpcServer server_config);
}
