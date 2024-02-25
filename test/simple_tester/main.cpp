#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QtQuick/QQuickView>
#include <quite/probe.hpp>

int main(int argc, char *argv[])
{
    quite::setupHooks();
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [] {
        qDebug() << "Hello from test app";
    });
    timer.start(1000);

    return QGuiApplication::exec();
}
