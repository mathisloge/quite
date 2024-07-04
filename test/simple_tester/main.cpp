#include <QDebug>
#include <QGuiApplication>
#include <QTimer>
#include <QtQuick/QQuickView>
#include <quite/probe.hpp>
#include <spdlog/spdlog.h>

#include <QQuickItem>

int main(int argc, char *argv[])
{
    quite::setupHooks();
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setObjectName("rootView");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    view.children();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [] { spdlog::debug("hello from test app"); });
    // timer.start(1000);

    return QGuiApplication::exec();
}
