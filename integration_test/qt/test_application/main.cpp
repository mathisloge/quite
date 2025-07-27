// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QDebug>
#include <QGuiApplication>
#include <QQuickItem>
#include <QtQuick/QQuickView>
#include <quite/probe.hpp>

int main(int argc, char *argv[])
{
    quite::setup_hooks(quite::GrpcServer{.server_address = "unix:///tmp/grpc_probe.sock"});
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setObjectName("rootView");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return QGuiApplication::exec();
}
