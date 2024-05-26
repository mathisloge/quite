#include <fmt/format.h>
#include <quite/value_handle.hpp>

namespace
{
struct ToStrVisitor
{
    std::string operator()(auto &&value) const
    {
        return fmt::format("{}", value);
    }
};
} // namespace

namespace quite
{
Value::Value() = default;
Value::~Value() = default;

std::string Value::to_str()
{
    const auto val = value();
    return std::visit(ToStrVisitor{}, val);
}
} // namespace quite
