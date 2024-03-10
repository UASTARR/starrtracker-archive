#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include <src/graph/Graph.h>
Q_DECLARE_METATYPE(GpsData)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serial( new QSerialPort(this) )
{
    ui->setupUi(this);
    ui->portSelect->clear();

    qRegisterMetaType<GpsData>();

    // Connect the connection lambda function to the clicked signal of serialConnectionButton
    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->serialLocalConnectionButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);

    // Connect the disconnection lambda function to the clicked signal of serialTerminationButton
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(ui->serialLocalTerminationButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);

    connect(&m_thread, &SerialThread::error, this, &MainWindow::handleError);
    connect(&m_thread, &SerialThread::dataReady, this, &MainWindow::handleDataReady);

    // Fixed: Shows indication if the GPS tracker stops recieving new packets.
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleSerialError);

    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ui->portSelect->addItem(serialPortInfo.portName()); // If working in WSL 2, you need to pass the USB connection through for this to work.
    }

    values[1] = new Graph(ui->graph_x);
    values[2] = new Graph(ui->graph_y);
    values[3] = new Graph(ui->graph_alt);
    values[1]->setGraph(-9000, 9000);
    values[2]->setGraph(-18000, 18000);
    values[3]->setGraph(0, 1800);
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

    delete values[1];
    delete values[2];
    delete values[3];
    delete ui;
}

void MainWindow::openSerialPort()
{
    QString path = ui->pathBrowser->toPlainText();
    ui->portSelect->setEnabled(false);
    ui->baudSelect->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->serialConnectionButton->setEnabled(false);
    ui->serialLocalConnectionButton->setEnabled(false);
    ui->serialTerminationButton->setEnabled(true);
    ui->serialLocalTerminationButton->setEnabled(true);
    if (path != ""){
        m_thread.startLocalDataThread(path);
    } else {
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        if (availablePorts.isEmpty()) {
            // No ports are available
            qDebug() << "No serial ports available.";
            handleError("No Ports Available");
        } else {
            QString port = ui->portSelect->currentText();
            int baud = ui->baudSelect->currentText().toInt();
            bool save = ui->saveButton->isChecked();
            if (!port.isEmpty() and !baud){
                m_thread.startSerialDataThread(port, baud, save);
                graphCount = 0;
            } else
                handleError("Could not open port. Insufficent information provided");
        }
    }
}

void MainWindow::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();

    m_thread.stopSerialThread();
    if (m_thread.wait(time))
    {
        QMessageBox::information(this,tr("Disconnected"),tr("Wow! The serial port closed!"));
        ui->serialConnectionButton->setEnabled(true);
        ui->serialLocalConnectionButton->setEnabled(true);
        ui->serialTerminationButton->setEnabled(false);
        ui->serialLocalTerminationButton->setEnabled(false);
        ui->portSelect->setEnabled(true);
        ui->baudSelect->setEnabled(true);
        ui->saveButton->setEnabled(true);
    }
    else {
        ui->serialTerminationButton->setEnabled(true);
        ui->serialLocalTerminationButton->setEnabled(true);
        QMessageBox::critical(this, tr("Critical Error"), tr("Failed to close thread"));
    }
}

//void MainWindow::handleSerialError(QSerialPort::SerialPortError error) {
//    if (error == QSerialPort::ResourceError) {
//        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
//        closeSerialPort();
//    }
//}

// Test: To check if this works. Have added automatic functionality to attempt reconnection every 5 second.
// Check: If UI is responsive when reconnection happens.
void MainWindow::handleSerialError(QSerialPort::SerialPortError error) {
    switch (error) {
        case QSerialPort::NotOpenError:
            QMessageBox::critical(this, tr("Critical Error"), tr("Serial port is not open."));
            closeSerialPort();
            break;
        case QSerialPort::ResourceError:
            QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
            closeSerialPort();
            break;
        case QSerialPort::TimeoutError:
            QMessageBox::critical(this, tr("Serial Port Error"), tr("Timeout error occurred."));
            closeSerialPort();
            break;

        default:
            QMessageBox::critical(this, tr("Unknown Error"), tr("An unknown error occurred."));
            break;
    }

    // Attempt automatic reconnection
    QTimer::singleShot(5000, this, &MainWindow::attemptSerialReconnect); // Retry after 5 seconds
}

void MainWindow::attemptSerialReconnect() {
    if (!m_serial->isOpen()) {
        if (m_serial->open(QIODevice::ReadWrite)) {
            qDebug() << "Serial port reconnected successfully.";
        } else {
            qDebug() << "Failed to reconnect to serial port:" << m_serial->errorString();
        }
    }
}

void MainWindow::handleError(const QString &s)
{
    QMessageBox::critical(this, tr("Critical Error"), s);
}

void MainWindow::handleDataReady(const GpsData &data)
{
    if (graphCount > checkCount){
        qt_time.removeFirst();
        qt_x.removeFirst();
        qt_y.removeFirst();
        qt_alt.removeFirst();
    } else {
        graphCount++;
    }

    qt_time.append(QTime(0,0,0).secsTo(data.time));
    qt_x.append(data.latitude);
    qt_y.append(data.longitude);
    qt_alt.append(data.altitude);

    ui->gpsType->setText(data.gps_name);
    ui->textBrowser->setText(tr("Time: %1\nLatitude: %2\nLongitude: %3\nAltitude: %4\n").arg(data.time.toString("HH:mm:ss"), QString::number(data.latitude), QString::number(data.longitude), QString::number(data.altitude)));

    values[1]->addGraph(qt_time, qt_x);
    values[2]->addGraph(qt_time, qt_y);
    values[3]->addGraph(qt_time, qt_alt);
}

void MainWindow::writeData(const QByteArray &data) {
    m_serial->write(data);
}
