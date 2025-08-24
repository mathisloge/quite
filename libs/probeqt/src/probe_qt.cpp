// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/probe_qt/probe_qt.hpp"
#include <quite/setup_logger.hpp>
#include "create_probe_context.hpp"

namespace quite::probe
{
Probe &setup_qt_probe(GrpcServer server_config)
{
    setup_logger(false);
    return create_probe_context(std::move(server_config));
}
} // namespace quite::probe
