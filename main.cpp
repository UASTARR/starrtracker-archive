#include "ui/mainwindow.h"
#include "src/map/streetmapview.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QQuickWidget>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/streetmapview.qml")));

    return a.exec();
}
