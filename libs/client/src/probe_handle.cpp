// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/client/probe_handle.hpp"

namespace quite::client
{
ProbeHandle::ProbeHandle(std::shared_ptr<Probe> probe)
    : probe_{std::move(probe)}
{}

Probe *ProbeHandle::operator->()
{
    return probe_.get();
}
} // namespace quite::client
