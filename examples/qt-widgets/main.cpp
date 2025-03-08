#include "mainwindow.h"

#include <QApplication>
#include <quite/probe.hpp>

int main(int argc, char *argv[])
{
    quite::setup_hooks();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
