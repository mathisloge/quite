#include <QDebug>
#include <QGuiApplication>
#include <QQuickItem>
#include <QtQuick/QQuickView>
#include <quite/probe.hpp>

int main(int argc, char *argv[])
{
    quite::setupHooks();
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setObjectName("rootView");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return QGuiApplication::exec();
}
