#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/map/streetmapview.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include <QQuickView>

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

//    engine->load(QUrl(QStringLiteral("qrc:/streetmapview.qml")));
//    QWindow *qml_window = qobject_cast<QWindow*>(engine->rootObjects().at(0));
//    QWidget *container = QWidget::createWindowContainer(qml_window, this);
//    container->setMinimumSize(200, 200);
//    container->setMaximumSize(1200, 900);

//    this->layout()->addWidget(container);

    QQuickWidget* streetmapview = new QQuickWidget();
    streetmapview->setSource(QUrl(QStringLiteral("qrc:/streetmapview.qml")));
    streetmapview->show();
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
