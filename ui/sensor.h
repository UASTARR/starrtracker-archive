#ifndef SENSOR_H
#define SENSOR_H

#include <QWidget>
#include <QSerialPort>
#include <QVariant>
#include <QtCore>
#include <QtGui>
#include <QtQuick>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QQmlContext>
#include <QQuickWidget>
#include <src/graph/Graph.h>
#include <src/graph/qcustomplot.h>
#include "../src/serial/serialthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Sensor; }
QT_END_NAMESPACE

class Sensor : public QWidget
{
    Q_OBJECT

private slots:
    void writeData(const QByteArray &data);
    void handleError(const QString &s);
    void handleDataReady(const GpsData &data);
    void handleConnectionStatus(const connectionStatus &status);
    void openSerialPort();
    void closeSerialPort();
    void on_prev_clicked();
    void on_next_clicked();
    void on_resetBtn1_clicked();
    void on_resetBtn2_clicked();
    void appendOutputData(const QString &data, const QString &color);

public:
    explicit Sensor(QWidget *parent = nullptr);
    ~Sensor();

private:
    Ui::Sensor *ui;
    QSerialPort *m_serial = nullptr;
    SerialThread m_thread;
    GPSParser m_parser;
    unsigned long time = 2000; // Time for program to wait for serialThread to close, in ms
    QMap<int, Graph*> values{};
    QVector<double> qt_time{}, qt_x{}, qt_y{}, qt_alt{};
    u_int graphCount{};
    u_int checkCount = 1000;
    float lat{}, lon{};
    void resetScreen();

    void setUIElementsEnabled(bool enabled);
signals:
    void setLocationMarker_1(QVariant, QVariant);
    void setLocationMarker_2(QVariant, QVariant);
    void clearFix(float, float);
};

#endif // SENSOR_H
