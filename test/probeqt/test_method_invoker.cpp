#include <catch2/catch_test_macros.hpp>
#include <entt/meta/resolve.hpp>
#include <fmt/printf.h>
#include <method_invoker.hpp>
#include <object_tracker.hpp>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>
#include <quite/value/value_registry.hpp>
#include <value_converters.hpp>

using namespace quite;
using namespace quite::probe;
using namespace entt::literals;

DEFINE_LOGGER(test)
namespace
{
class MyTestClass : public QObject
{
    Q_OBJECT

  public Q_SLOTS:
    quint64 compute(quint64 val1, quint8 val2)
    {
        return val1 + val2;
    }

    double compute(float val1, qint8 val2)
    {
        return val1 * static_cast<float>(val2);
    }

    void invoke_me()
    {}
};

} // namespace

TEST_CASE("Test MethodInvoker")
{
    setup_logger();
    entt::locator<ValueRegistry>::emplace();
    register_converters();
    ObjectTracker tracker{};
    MethodInvoker method_invoker{tracker};
    MyTestClass my_test_class;
    SECTION("Test with different types")
    {
        constexpr double val1{1.5};
        constexpr int val2{2};
        std::vector<entt::meta_any> params{entt::meta_any{val1}, entt::meta_any{val2}};
        auto result = method_invoker.invoke_method(
            entt::meta_any{static_cast<QObject *>(&my_test_class)}, "compute(float, qint8)", params);
        REQUIRE(result.has_value());
        REQUIRE(result.value().type() == entt::resolve("double"_hs));
        const auto expected_result = val1 * val2;
        // v result == 3
        REQUIRE(std::abs(expected_result - *static_cast<const double *>(result.value().base().data())) <
                std::numeric_limits<double>::epsilon());
    }

    SECTION("Test with void")
    {
        auto result =
            method_invoker.invoke_method(entt::meta_any{static_cast<QObject *>(&my_test_class)}, "invoke_me()", {});
        REQUIRE(result.has_value());
        REQUIRE(result->type().info() == entt::type_id<void>());
    }
}

#include "test_method_invoker.moc"
