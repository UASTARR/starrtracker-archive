#include "serialthread.h"

#include <QSerialPort>
#include <QDebug>
#include <QFile>

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

void SerialThread::startLocalDataThread(const QString &file)
{
    const QMutexLocker locker(&m_mutex);
    m_file = file;
    m_save_data = false;
    m_serial_mode = false;
    if (!isRunning())
    {
        start();
    }
}

void SerialThread::startSerialDataThread(const QString &port, const qint32 &baud, const bool &saveData)
{
    const QMutexLocker locker(&m_mutex);
    m_port = port;
    m_baud  = baud;
    m_save_data = saveData;
    m_serial_mode = true;
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
    m_serial_mode = false;
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

QString SerialThread::getFile()
{
   QString temp;
   m_mutex.lock();
   temp = m_file;
   m_mutex.unlock();
   return temp;
}

void SerialThread::run()
{
    if (m_serial_mode)  // Serial Mode
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
            QString data;
            GpsData result;
            serial.clear();
            while (serial.waitForReadyRead(-1))
            {
                while (serial.canReadLine())
                {
                    data = QString::fromLocal8Bit(serial.readLine());
                    result = m_gpsTracker.parse(data, m_save_data);
                    if (result.valid)
                    {
                        emit dataReady(result);
                        qDebug() << "Sending data...\n" << result.gps_name << Qt::endl;
                    }
                    else
                    {
                        qDebug() << "Invalid data blocked" << Qt::endl;
                    }
                }
                if (getStopFlag())
                {
                    break;
                }
            }
        }

        serial.close();
    }
    else    // File mode
    {
        GpsData result;
        QFile file(getFile());
        if(!file.open(QIODevice::ReadOnly)) {
            emit error(tr("Failed to open file, error: %1").arg(file.errorString()));
        }

        QTextStream in(&file);

        while(!in.atEnd()) {
            QString data = in.readLine();
            if (data != ""){
                result = m_gpsTracker.parse(data, m_save_data);
                if (result.valid)
                {
                    emit dataReady(result);
                    qDebug() << "Sending data...\n" << result.gps_name << Qt::endl;
                }
                else
                {
                    qDebug() << "Invalid data blocked" << Qt::endl;
                }
            }
        }

        file.close();
    }
}
