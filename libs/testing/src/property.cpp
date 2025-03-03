#include "quite/test/property.hpp"
#include <quite/property.hpp>
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

    auto operator()(const xyz::indirect<ArrayObject> & /*unused*/) -> Property::Value
    {
        return {};
    }
    auto operator()(const xyz::indirect<ClassObject> & /*unused*/) -> Property::Value
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

void Property::write(Value value)
{}
} // namespace quite::test
