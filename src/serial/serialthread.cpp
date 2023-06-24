#include "serialthread.h"

#include <QSerialPort>
#include <QDebug>

SerialThread::SerialThread(QObject *parent)
    : QThread(parent)
    , m_gpsTracker()
{

}

SerialThread::~SerialThread()
{
    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
    wait();
}

void SerialThread::startSerialThread(const QString &port)
{
    const QMutexLocker locker(&m_mutex);
    m_port = port;
    if (!isRunning())
    {
        start();
    }
}

void SerialThread::stopSerialThread()
{
    m_mutex.lock();
    m_quit = true;
    m_mutex.unlock();
}

void SerialThread::run()
{
    m_mutex.lock();
    // Stuff
    QString currentPort = m_port;
    m_mutex.unlock();

    QSerialPort serial;

    while (!m_quit)
    {
        serial.setPortName(currentPort);
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        if (!serial.open(QIODevice::ReadWrite))
        {
            emit error(tr("Failed to open port %1, error: %2").arg(m_port).arg(serial.error()));
            return;
        }

        QByteArray data;
        while (serial.waitForReadyRead(-1))
        {
            while (serial.canReadLine())
            {
                data = serial.readLine();
                m_gpsTracker.parse(data);
            }
//            char buf[1024];
//            qint64 lineLength = serial.readLine(buf, sizeof(buf));
//            if (lineLength != -1)
//            {
//                data = QByteArray::fromRawData(buf,lineLength);
//                m_gpsTracker.parse(data);
//            }
        }

    serial.close();

    }
}
