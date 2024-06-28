#include <fmt/format.h>
#include <quite/property.hpp>
#include <quite/remote_object.hpp>
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

    auto operator()(const std::shared_ptr<quite::RemoteObject> &object) const
    {
        return fmt::format_to(ctx.out(), "{}", "remote_object");
    }

    auto operator()(const xyz::indirect<quite::ArrayObject> &array) const
    {
        return fmt::format_to(ctx.out(), "{}", "array");
    }
};
} // namespace

auto fmt::formatter<quite::Value>::format(const quite::Value &v, format_context &ctx) const -> format_context::iterator
{
    return std::visit(ToStrVisitor{ctx}, v);
}
