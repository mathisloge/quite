#include <fmt/format.h>
#include <quite/property.hpp>
namespace quite
{

Property::~Property() = default;

} // namespace quite

namespace
{
struct ToStrVisitor
{
    fmt::format_context &ctx;
    auto operator()(auto &&value) const
    {
        return fmt::format_to(ctx.out(), "{}", value);
    }
};
} // namespace

auto fmt::formatter<quite::Value>::format(const quite::Value &v, format_context &ctx) const -> format_context::iterator
{
    return std::visit(ToStrVisitor{ctx}, v);
}
