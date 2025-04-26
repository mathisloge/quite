#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <quite/probe.hpp>

int main(int argc, char *argv[])
{
    quite::setup_hooks();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Example.Qml", "Main");

    return app.exec();
}
