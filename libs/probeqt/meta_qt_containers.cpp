#include <QList>
#include <entt/meta/container.hpp>
#include <entt/meta/factory.hpp>
#include <quite/value/value_registry.hpp>
namespace entt
{
template <typename... Args>
struct meta_sequence_container_traits<QList<Args...>> : basic_meta_sequence_container_traits<QList<Args...>>
{};
} // namespace entt

#include "meta_qt_containers.hpp"

namespace quite::experimental
{
template <typename Type>
auto test()
{
    using namespace entt;
    using namespace entt::internal;

    const auto type_traits =
        (std::is_arithmetic_v<Type> ? meta_traits::is_arithmetic : meta_traits::is_none) |
        (std::is_integral_v<Type> ? meta_traits::is_integral : meta_traits::is_none) |
        (std::is_signed_v<Type> ? meta_traits::is_signed : meta_traits::is_none) |
        (std::is_array_v<Type> ? meta_traits::is_array : meta_traits::is_none) |
        (std::is_enum_v<Type> ? meta_traits::is_enum : meta_traits::is_none) |
        (std::is_class_v<Type> ? meta_traits::is_class : meta_traits::is_none) |
        (std::is_pointer_v<Type> ? meta_traits::is_pointer : meta_traits::is_none) |
        (is_meta_pointer_like_v<Type> ? meta_traits::is_pointer_like : meta_traits::is_none) |
        (is_complete_v<meta_sequence_container_traits<Type>> ? meta_traits::is_sequence_container
                                                             : meta_traits::is_none) |
        (is_complete_v<meta_associative_container_traits<Type>> ? meta_traits::is_associative_container
                                                                : meta_traits::is_none);
    return type_traits;
}

void testRegister()
{
    static_assert(entt::is_complete_v<entt::meta_sequence_container_traits<QList<QObject *>>>, "");
    auto &value_registry = entt::locator<ValueRegistry>::value();
    test<QList<int>>();
    // entt::meta_factory<QList<int>>();
    entt::meta_factory<QList<int>>();
    std::ignore = entt::internal::resolve<QList<int>>(entt::internal::meta_context::from(value_registry.context()));
}
} // namespace quite::experimental
