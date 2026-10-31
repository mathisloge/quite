// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/client/probe_context_handle.hpp"

namespace quite::client
{
ProbeContextHandle::ProbeContextHandle(std::shared_ptr<ProbeContext> probe_context)
    : probe_context_{std::move(probe_context)}
{}

ProbeContext *ProbeContextHandle::operator->()
{
    return probe_context_.get();
}
} // namespace quite::client
