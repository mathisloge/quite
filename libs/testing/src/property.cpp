#include "quite/test/property.hpp"
#include <quite/property.hpp>

namespace quite::test
{
Property::Property(std::shared_ptr<quite::Property> property)
    : property_{std::move(property)}
{}

Property::Value Property::fetch()
{
    const auto [result] = stdexec::sync_wait(property_->read()).value();
}

const Property::Value &Property::value() const
{}

void Property::write(Value value)
{}
} // namespace quite::test
