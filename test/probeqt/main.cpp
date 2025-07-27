#include <QCoreApplication>
#include <catch2/catch_session.hpp>
#include <quite/setup_logger.hpp>

int main(int argc, char **argv)
{
    quite::setup_logger();
    QCoreApplication app(argc, argv);
    return Catch::Session().run(argc, argv);
}
