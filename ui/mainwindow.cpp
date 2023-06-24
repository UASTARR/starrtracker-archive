#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serial( new QSerialPort(this) )
{
    ui->setupUi(this);
    ui->lineEdit->setValidator( new QIntValidator(300,250000,this) ); // LineEdit Could be used for Baud Rate selection, though it's not an elegant solution. Does nothing currently.
    ui->comboBox->clear(); // Pointless?

    //connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    //connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(&m_thread, &SerialThread::error, this, &MainWindow::handleThreadError);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ui->comboBox->addItem(serialPortInfo.portName()); // If working in WSL 2, you need to pass the USB connection through for this to work.
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openSerialPort() {


    ui->serialConnectionButton->setEnabled(false);

//    m_serial->setPortName(ui->comboBox->currentText());
//    m_serial->setBaudRate(QSerialPort::Baud9600);
//    m_serial->setDataBits(QSerialPort::Data8);
//    m_serial->setParity(QSerialPort::NoParity);
//    m_serial->setStopBits(QSerialPort::OneStop);
//    m_serial->setFlowControl(QSerialPort::NoFlowControl);
//    if (m_serial->open(QIODevice::ReadWrite)) {
//        // UI logic here?
//    } else {
//        QMessageBox::critical(this, tr("Error"), m_serial->errorString());
//    }

    m_thread.startSerialThread(ui->comboBox->currentText());
}

void MainWindow::closeSerialPort() {
//    if (m_serial->isOpen())
//        m_serial->close();

    m_thread.stopSerialThread();
    QMessageBox::information(this,tr("Disconnected"),tr("Wow! The serial port closed!"));
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

void MainWindow::writeData(const QByteArray &data) {
    m_serial->write(data);
}

void MainWindow::readData() {
    //const QByteArray data = m_serial->readAll();
    //std::cout << data.constData(); // This only sometimes works and can be seen in the Application Output. The issue is probably with readAll(). This should be removed and replaced by actual data processing.
}
