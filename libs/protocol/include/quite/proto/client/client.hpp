// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <memory>
#include <quite/asio_config.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/value/value_registry.hpp>
#include "quite/quite_protocol_export.hpp"

namespace quite::proto
{
class IValueConverter;
class ProbeClient;
class QUITE_PROTOCOL_EXPORT Client final
{
  public:
    QUITE_DISABLE_COPY_MOVE(Client);
    explicit Client(entt::locator<ValueRegistry>::node_type value_registry);
    ~Client();
    std::shared_ptr<ProbeClient> create_probe_client(std::shared_ptr<IValueConverter> value_converter,
                                                     std::string connection_url);

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::proto
