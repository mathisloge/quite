// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/probe.hpp>
#include "quite/quite_probe_qt_export.hpp"

namespace quite::probe
{
PROBE_QT_EXPORT Probe &setup_qt_probe(GrpcServer server_config = GrpcServer{
                                          .server_address = "unix:///tmp/grpc_probe.sock"});
}
