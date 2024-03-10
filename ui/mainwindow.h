#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <src/graph/Graph.h>
#include <src/graph/qcustomplot.h>
#include "../src/serial/serialthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void writeData(const QByteArray &data);

    void handleSerialError(QSerialPort::SerialPortError error);
    void handleError(const QString &s);
    void handleDataReady(const GpsData &data);

    void openSerialPort();
    void closeSerialPort();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial = nullptr;
    SerialThread m_thread;
    unsigned long time = 5000; // Time for program to wait for serialThread to close, in ms
    QMap<int, Graph*> values;
    QVector<double> qt_time, qt_x, qt_y, qt_alt;
    u_int graphCount = 0;
    u_int checkCount = 1000;
    void attemptSerialReconnect();
};
#endif // MAINWINDOW_H
