#include <iostream>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <quite/probe.hpp>

int main(int argc, char *argv[])
{
    quite::setupHooks();
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();
    return QGuiApplication::exec();
}
