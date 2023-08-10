#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    ui->baudSelect->setValidator( new QIntValidator(300,250000,this) ); // LineEdit Could be used for Baud Rate selection, though it's not an elegant solution. Does nothing currently.
    ui->baudSelect->setEnabled(false); // Enable when baud rate can be changed
    ui->comboBox->clear(); // Pointless?

    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(&m_thread, &SerialThread::error, this, &MainWindow::handleThreadError);
    connect(&m_thread, &SerialThread::dataReady, this, &MainWindow::handleDataReady);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ui->comboBox->addItem(serialPortInfo.portName()); // If working in WSL 2, you need to pass the USB connection through for this to work.
    }


}

MainWindow::~MainWindow()
{
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
    ui->serialConnectionButton->setEnabled(false);
    ui->serialTerminationButton->setEnabled(true);

    m_thread.startSerialThread(ui->comboBox->currentText());
}

void MainWindow::closeSerialPort() {
    if (m_serial->isOpen())
        m_serial->close();

    m_thread.stopSerialThread();

    if (m_thread.wait(time))
    {
        QMessageBox::information(this,tr("Disconnected"),tr("Wow! The serial port closed!"));
        ui->serialConnectionButton->setEnabled(true);
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

void MainWindow::readData() {
    //const QByteArray data = m_serial->readAll();
    //std::cout << data.constData(); // This only sometimes works and can be seen in the Application Output. The issue is probably with readAll(). This should be removed and replaced by actual data processing.
}
