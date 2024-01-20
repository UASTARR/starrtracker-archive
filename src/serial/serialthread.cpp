#include "serialthread.h"

#include <QSerialPort>
#include <QDebug>

SerialThread::SerialThread(QObject *parent)
    : QThread(parent)
    , m_gpsTracker()
{
    m_stop = false;
}

SerialThread::~SerialThread()
{
    setStopFlag(true);
    wait();
}

void SerialThread::startSerialDataThread(const QString &port, const qint32 &baud)
{
    const QMutexLocker locker(&m_mutex);
    m_port = port;
    m_baud  = baud;
    if (!isRunning())
    {
        start();
    }
}

void SerialThread::stopSerialThread()
{
    setStopFlag(true);
}

void SerialThread::setStopFlag(bool newState)
{
    m_mutex.lock();
    m_stop = newState;
    m_mutex.unlock();
}

bool SerialThread::getStopFlag()
{
    bool temp;
    m_mutex.lock();
    temp = m_stop;
    m_mutex.unlock();
    return temp;
}

QString SerialThread::getPort()
{
    QString temp;
    m_mutex.lock();
    temp = m_port;
    m_mutex.unlock();
    return temp;
}

qint32 SerialThread::getBaud()
{
    qint32 temp;
    m_mutex.lock();
    temp = m_baud;
    m_mutex.unlock();
    return temp;
}

void SerialThread::run()
{
    QSerialPort serial;
    QString port;
    qint32 baudRate;

    port = getPort();
    baudRate = getBaud();
    serial.setPortName(port);
    serial.setBaudRate(baudRate);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial.open(QIODevice::ReadWrite))
    {
        emit error(tr("Failed to open port %1, error: %2").arg(port).arg(serial.error()));

        return;
    }
    else
    {
        QByteArray data;
        GpsData result;
        while (serial.waitForReadyRead(-1))
        {
            while (serial.canReadLine())
            {
                data = serial.readLine();
                result = m_gpsTracker.parse(data);
                if (result.valid)
                    emit dataReady(result);
            }
            if (getStopFlag())
            {
                break;
            }
        }
    }

    serial.close();
}
