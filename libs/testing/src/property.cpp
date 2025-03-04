#include "quite/test/property.hpp"
#include <boost/asio/steady_timer.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <quite/property.hpp>
#include <quite/quite.hpp>
#include "quite/test/remote_object.hpp"
#include "throw_unexpected.hpp"

namespace quite::test
{
struct Converter
{
    auto operator()(std::shared_ptr<quite::RemoteObject> value) -> Property::Value
    {
        return quite::test::RemoteObject{std::move(value)};
    }

    auto operator()(xyz::indirect<quite::ArrayObject> /*unused*/) -> Property::Value
    {
        return {};
    }
    auto operator()(xyz::indirect<quite::ClassObject> /*unused*/) -> Property::Value
    {
        return {};
    }
    auto operator()(auto &&value) -> Property::Value
    {
        return value;
    }
};

Property::Property(std::shared_ptr<quite::Property> property)
    : property_{std::move(property)}
{}

Property::Value Property::fetch()
{
    const auto [result] = stdexec::sync_wait(property_->read()).value();
    throw_unexpected(result);
    return std::visit(Converter{}, result.value());
}

Property::Value Property::value() const
{
    auto &&value = property_->value();
    throw_unexpected(value);
    return std::visit(Converter{}, *value);
}

void Property::write(Property::Value value)
{}

Property::Value Property::wait_for_value(Property::Value target_value, std::chrono::milliseconds timeout)
{
    Property::Value return_value{};

    boost::asio::steady_timer timeout_timer{asio_context().get_executor(), timeout};
    stdexec::sender auto timeout_snd =
        timeout_timer.async_wait(asio2exec::use_sender) | stdexec::then([]([[maybe_unused]] auto &&ec) {});

    stdexec::sender auto fetch_value_snd =
        stdexec::schedule(asio_context().get_scheduler()) | stdexec::let_value([this]() { return property_->read(); }) |
        stdexec::then([&return_value, &target_value](auto &&possible_value) -> bool {
            if (not possible_value.has_value())
            {
                return false;
            }
            return_value = std::visit(Converter{}, possible_value.value());
            return return_value == target_value;
        }) |
        stdexec::let_value([](bool finished) -> exec::task<bool> {
            if (not finished)
            {
                boost::asio::steady_timer retry_timer{asio_context().get_executor(), std::chrono::milliseconds{100}};
                co_await retry_timer.async_wait(asio2exec::use_sender);
            }
            co_return finished;
        }) |
        exec::repeat_effect_until();

    stdexec::sender auto wait_snd = exec::when_any(std::move(fetch_value_snd), std::move(timeout_snd));
    stdexec::sync_wait(std::move(wait_snd));

    return return_value;
}
} // namespace quite::test
