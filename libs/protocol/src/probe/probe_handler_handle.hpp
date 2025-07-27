// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/service_handle.hpp>
#include "quite/proto/probe/probe_handler.hpp"
namespace quite::proto
{
class IProbeHandler;
using ProbeHandlerHandle = ServiceHandle<IProbeHandler>;
} // namespace quite::proto
