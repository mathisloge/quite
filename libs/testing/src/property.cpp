// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/test/property.hpp"
#include <boost/asio/steady_timer.hpp>
#include <asioexec/use_sender.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <quite/client/property.hpp>
#include <quite/client/quite.hpp>
#include <quite/logger.hpp>
#include <quite/meta_any_formatter.hpp>
#include "quite/asio_context.hpp"
#include "quite/test/remote_object.hpp"
#include "throw_unexpected.hpp"
#include "value_convert.hpp"

DEFINE_LOGGER(test_property);

namespace quite::test
{
Property::Property(std::shared_ptr<client::Property> property)
    : property_{std::move(property)}
{}

Property::Value Property::fetch()
{
    const auto [result] = stdexec::sync_wait(property_->read()).value();
    throw_unexpected(result);
    return convert_any(result.value());
}

Property::Value Property::value() const
{
    auto &&value = property_->value();
    throw_unexpected(value);
    return convert_any(*value);
}

void Property::write(Property::Value value)
{
    const auto [write_result] = stdexec::sync_wait(property_->write(convert_any(std::move(value)))).value();
    throw_unexpected(write_result);
}

Property::Value Property::wait_for_value(Property::Value target_value, std::chrono::milliseconds timeout)
{
    Property::Value return_value{};

    boost::asio::steady_timer timeout_timer{get_executor(), timeout};

    stdexec::sender auto fetch_value_snd =
        stdexec::schedule(client::asio_context().get_scheduler()) |
        stdexec::let_value([this]() { return property_->read(); }) |
        stdexec::then([&return_value, &target_value](auto &&possible_value) -> bool {
            if (not possible_value.has_value())
            {
                return false;
            }
            return_value = convert_any(possible_value.value());
            return return_value == target_value;
        }) |
        stdexec::let_value([](bool finished) -> exec::task<bool> {
            if (not finished)
            {
                boost::asio::steady_timer retry_timer{get_executor(), std::chrono::milliseconds{100}};
                co_await retry_timer.async_wait(asioexec::use_sender);
            }
            co_return finished;
        }) |
        exec::repeat_effect_until();

    stdexec::sender auto timeout_snd = timeout_timer.async_wait(asioexec::use_sender);
    stdexec::sender auto wait_snd = exec::when_any(std::move(fetch_value_snd), std::move(timeout_snd));
    stdexec::sync_wait(std::move(wait_snd));

    return return_value;
}
} // namespace quite::test
