#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/graph/qcustomplot.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serial( new QSerialPort(this) )
{
    ui->setupUi(this);
    ui->portSelect->clear();

    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(&m_thread, &SerialThread::error, this, &MainWindow::handleThreadError);     // Error
    connect(&m_thread, &SerialThread::dataReady, this, &MainWindow::handleDataReady);   // Data
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ui->portSelect->addItem(serialPortInfo.portName()); // If working in WSL 2, you need to pass the USB connection through for this to work.
    }

    // Use the emit signal of data ready in serial thread to parse the data.
    // Take the data and store it in a var
    ui->layout_graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->layout_graph->addGraph();       // TO add more lines, insert more of these statements
    ui->layout_graph->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->layout_graph->xAxis->setTicker(timeTicker);
    ui->layout_graph->axisRect()->setupFullAxesBox();
    ui->layout_graph->yAxis->setRange(-1.2, 1.2);
    // ui->layout_graph->yAxis->setRange(0, 1000);      // Y axis

    // Change the axis range in real time
    connect(ui->layout_graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->layout_graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->layout_graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->layout_graph->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QTimer dataTimer;
    //connect(dataTimer, &QTimer::timeout, this, SLOT(realtimeDataSlot()));
    //dataTimer->start(1000); // Interval 0 means to refresh as fast as possible
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0);

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
    ui->gpsType->setText(data[0]);
    ui->textBrowser->setText(data[1]);
}

void MainWindow::writeData(const QByteArray &data) {
    m_serial->write(data);
}

void MainWindow::realtimeDataSlot(){
    QElapsedTimer elapsedTime;
    double key = elapsedTime.elapsed()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      ui->layout_graph->graph(0)->addData(key, qSin(key)/(double)RAND_MAX*1*qSin(key/0.3843));
      // rescale value (vertical) axis to fit the current data:
      //ui->layout_graph->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->layout_graph->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->layout_graph->replot();
    ui->layout_graph->update();
}

