#include <catch2/catch_test_macros.hpp>
#include <entt/meta/resolve.hpp>
#include <fmt/printf.h>
#include <method_invoker.hpp>
#include <value_converters.hpp>
using namespace quite;
using namespace quite::probe;
using namespace entt::literals;
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
};

} // namespace

TEST_CASE("Test MethodInvoker")
{
    register_converters();
    ObjectTracker tracker{};
    MethodInvoker method_invoker{tracker};

    MyTestClass my_test_class;
    std::vector<entt::meta_any> params{entt::meta_any{1.5}, entt::meta_any{2}};
    auto result = method_invoker.invoke_method(
        entt::meta_any{static_cast<QObject *>(&my_test_class)}, "compute(float, qint8)", params);
    REQUIRE(result.has_value());
    REQUIRE(result.value().type() == entt::resolve("double"_hs));
    // v result == 3
    REQUIRE(std::abs(3 - *static_cast<double *>(result.value().data())) < std::numeric_limits<double>::epsilon());

    // delete result.value().data();
}

#include "tets_method_invoker.moc"
