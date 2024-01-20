#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "../src/serial/serialthread.h"
#include "src/graph/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);

    void handleError(QSerialPort::SerialPortError error);
    void handleThreadError(const QString &s);
    void handleDataReady(const GpsData &data);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial = nullptr;
    SerialThread m_thread;
    unsigned long time = 5000; // Time for program to wait for serialThread to close, in ms
    QVector<double> qt_time;
    QVector<double> qt_x, qt_y, qt_alt;
    QList<QCustomPlot *> values;
};
#endif // MAINWINDOW_H
