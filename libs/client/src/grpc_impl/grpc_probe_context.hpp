// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include "quite/client/probe_context.hpp"
#include "quite/proto/client/probe_client.hpp"

namespace quite::client
{
class GrpcProbeContext final : public ProbeContext
{
  public:
    void set_client(std::shared_ptr<proto::ProbeClient> client);
    proto::ProbeClient &client();

    core::IMouseInjector &mouse_injector() override;

  private:
    std::shared_ptr<proto::ProbeClient> client_;
};
} // namespace quite::client
