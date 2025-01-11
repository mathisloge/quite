#include <QDebug>
#include <QGuiApplication>
#include <QQuickItem>
#include <QtQuick/QQuickView>
#include <quite/probe.hpp>
#include "MyCustomType.hpp"

int main(int argc, char *argv[])
{
    quite::setup_hooks();
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setObjectName("rootView");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    MyCustomType my_custom_type_instance;

    return QGuiApplication::exec();
}
