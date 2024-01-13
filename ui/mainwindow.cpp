#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serial( new QSerialPort(this) )
{
    ui->setupUi(this);
    ui->portSelect->clear();

    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(&m_thread, &SerialThread::error, this, &MainWindow::handleThreadError);
    connect(&m_thread, &SerialThread::dataReady, this, &MainWindow::handleDataReady);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ui->portSelect->addItem(serialPortInfo.portName()); // If working in WSL 2, you need to pass the USB connection through for this to work.
    }

    values << ui->graph_x << ui->graph_y << ui->graph_alt;

    // Graphing setup
    foreach(QCustomPlot *plot, values){
        plot->addGraph();
        plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        plot->graph(0)->setLineStyle(QCPGraph::lsLine);
        plot->xAxis->setLabel("Time");          // X label
        plot->xAxis->setRange(0, 1800);   // Range of x
        plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

//         Test to check if graph works
//        qt_time = {1, 2, 3, 4, 5, 6, 7};
//        qt_x = {4, 5, 3, 7, 2, 8, 9};
//        plot->graph(0)->setData(qt_time, qt_x);
//        plot->rescaleAxes();
//        plot->replot();
//        plot->update();
    }

    ui->graph_x->yAxis->setRange(-9000, 9000);
    ui->graph_y->yAxis->setRange(-18000, 18000);
    ui->graph_alt->yAxis->setRange(0, 1800);
}

MainWindow::~MainWindow()
{
    if (m_serial->isOpen())
        m_serial->close();

    // If  serialThread is still running, try closing port. If that doesn't work, serial thread is force closed
    if (m_thread.isRunning())
    {
        closeSerialPort();
        if (m_thread.isRunning())
        {
            QTextStream(stdout) <<  tr("Warning: Force quit serialThread\n");
            m_thread.terminate();
        }
    }

    delete ui;
}


void MainWindow::openSerialPort()
{
    ui->portSelect->setEnabled(false);
    ui->baudSelect->setEnabled(false);
    ui->serialConnectionButton->setEnabled(false);
    ui->serialTerminationButton->setEnabled(true);

    m_thread.startSerialThread(ui->portSelect->currentText(), (ui->baudSelect->currentText()).toInt(nullptr, 10));
}

void MainWindow::closeSerialPort() {
    if (m_serial->isOpen())
        m_serial->close();

    m_thread.stopSerialThread();

    if (m_thread.wait(time))
    {
        QMessageBox::information(this,tr("Disconnected"),tr("Wow! The serial port closed!"));
        ui->serialTerminationButton->setEnabled(false);
    }
    else
        QMessageBox::critical(this, tr("Critical Error"), tr("Failed to close thread"));
}

void MainWindow::handleThreadError(const QString &s)
{
    QMessageBox::critical(this, tr("Critical Error"), s);
}

void MainWindow::handleError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::handleDataReady(const QStringList &data)
{
    // Possible optimization, check if length of vector exceeded certain limit and clear it after that
    // change below based on featherweight gps data.

    // Storing all data to vectors
    qt_time.append(data[1].toDouble());
    if (data[3] == "N") qt_x.append(data[2].toDouble());        // + for N
        else qt_x.append(-data[2].toDouble());                  // - for S
    if (data[5] == "E") qt_y.append(data[4].toDouble());        // + for E
        else qt_y.append(-data[4].toDouble());                  // - for W
    if (data[10] == "m" or data[10] == "M") qt_alt.append(data[9].toDouble());     // altitude in m
        else qt_alt.append(0.3048*data[9].toDouble());          // Convert feet to m

    ui->gpsType->setText(data[0]);
    ui->textBrowser->setText(tr("Time: %1\nLatitude: %2 %3\nLongitude: %4 %5\nAltitude: %6 %7\n").arg(data[1],data[2],data[3],data[4],data[5],data[6],data[7]));

    ui->graph_x->graph(0)->setData(qt_time, qt_x);
    ui->graph_y->graph(0)->setData(qt_time, qt_y);
    ui->graph_alt->graph(0)->setData(qt_time, qt_alt);

    foreach(QCustomPlot *plot, values){
        plot->rescaleAxes();
        plot->replot();
        plot->update();
    }
}

void MainWindow::writeData(const QByteArray &data) {
    m_serial->write(data);
}
