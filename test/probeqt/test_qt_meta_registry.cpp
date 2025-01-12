#include <QObject>
#include <catch2/catch_test_macros.hpp>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>
#include "qt_meta_registry.hpp"
#include "value_converters.hpp"

using namespace quite;
using namespace quite::probe;

DEFINE_LOGGER(test);

class MyTestClassMetaRegistry : public QObject
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

TEST_CASE("Test QtMetaRegistry", "[meta]")
{
    setup_logger();
    register_converters();
    QtMetaRegistry meta_registry;
    SECTION("Lookup QObject type")
    {

        stdexec::sync_wait([&]() -> exec::task<void> {
            const auto lookup_result =
                co_await meta_registry.lookup_type(QMetaType::fromType<MyTestClassMetaRegistry>().id());
            if (not lookup_result.has_value())
            {
                LOG_DEBUG(test, "Result of {}", lookup_result.error().message);
            }
            else
            {

                LOG_DEBUG(test, "Result of {}", fmt::format("{}", lookup_result.value()));
            }
            REQUIRE(lookup_result.has_value());
        }());
    }
}
#include "test_qt_meta_registry.moc"
