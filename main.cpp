#include "ui/mainwindow.h"
#include "streetmapview.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSerialPortInfo>
#include <QComboBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    StreetMapView *map = new StreetMapView(&w);

    map->show();
    w.show();

    return a.exec();
}
