#include "serialthread.h"

SerialThread::SerialThread(QObject *parent)
    : QThread(parent)
    , m_gpsTracker()
{
    connect(this, &SerialThread::clearFix, &m_gpsTracker, &GPSParser::clearFix);
    m_stop = false;
}

SerialThread::~SerialThread()
{
    setStopFlag(true);
    wait();  // Ensure the thread has finished before destroying the object
}

void SerialThread::startLocalDataThread(const QString &file)
{
    {
        const QMutexLocker locker(&m_mutex);
        m_file = file;
        m_save_data = false;
        m_serial_mode = false;
        m_stop = false;
    }

    if (!isRunning())
    {
        start();
    }

    resetTimer();
}

void SerialThread::startSerialDataThread(const QString &port, const qint32 &baud, const bool &saveData)
{
    {
        const QMutexLocker locker(&m_mutex);
        m_port = port;
        m_baud  = baud;
        m_save_data = saveData;
        m_serial_mode = true;
        m_stop = false;
    }

    if (!isRunning())
    {
        start();
    }

    resetTimer();
}

void SerialThread::stopSerialThread()
{
    setStopFlag(true);
    wait(time);  // Wait for the thread to finish
    timeouttimer.stop();
    disconnect(connection);
}

void SerialThread::setStopFlag(bool newState)
{
    const QMutexLocker locker(&m_mutex);
    m_stop = newState;
}

bool SerialThread::getStopFlag()
{
    // Previously used code:
    // bool temp;
    // m_mutex.lock();
    // temp = m_stop;
    // m_mutex.unlock();
    // return temp;

    // Better Version
    const QMutexLocker locker(&m_mutex);
    return m_stop;
}

QString SerialThread::getPort()
{
    const QMutexLocker locker(&m_mutex);
    return m_port;
}

qint32 SerialThread::getBaud()
{
    const QMutexLocker locker(&m_mutex);
    return m_baud;
}

QString SerialThread::getFile()
{
    const QMutexLocker locker(&m_mutex);
    return m_file;
}

void SerialThread::run()
{
    if (m_serial_mode)  // Serial Mode
    {
        QSerialPort serial;
        QString port = getPort();
        qint32 baudRate = getBaud();

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

        QString data;
        /*
         * Looking for the following string:
         * manufacturer     altusmetrum.org
         * product          TeleBT-v4.0
         * serial-number    12056
         * program-space    28672
         */
        QString teleGPSCheck = "manufacturer     altusmetrum.org";  // Need to make this better.
        serial.clear();
        serial.write("v\n");

        while (serial.waitForReadyRead(-1) && !getStopFlag())
        {
            while (serial.canReadLine())
            {
                data = QString::fromLocal8Bit(serial.readLine()).trimmed();
                if (data == teleGPSCheck){
                    serial.write("m34\n");
                }
                if (!data.isEmpty()){
                    emit appendData(data, "black");

                    m_gpsTracker.parse(data, m_save_data, m_serial_mode);
                    if (m_gpsTracker.validateData())
                    {
                        emit dataReady(m_gpsTracker.getData());
                        emit appendData(QString("Sending data ... %1 \n").arg(m_gpsTracker.getGpsName()), "blue");
                        m_gpsTracker.clearData();
                        m_gpsTracker.StartTimer();
                    }
                }
            }
        }

        serial.close();
    }
    else    // File mode
    {
        QFile file(getFile());
        if (!file.open(QIODevice::ReadOnly)) {
            emit error(tr("Failed to open file, error: %1").arg(file.errorString()));
            return;
        }

        QTextStream in(&file);

        while (!in.atEnd() && !getStopFlag()) {
            QString data = in.readLine();
            if (!data.isEmpty()){
                emit appendData(data, "black");
                if (data != ""){
                    m_gpsTracker.parse(data, m_save_data, m_serial_mode);
                    if (m_gpsTracker.validateData())
                    {
                        emit dataReady(m_gpsTracker.getData());
                        emit appendData(QString("Sending data ... %1 \n").arg(m_gpsTracker.getGpsName()), "blue");
                        m_gpsTracker.clearData();
                        m_gpsTracker.StartTimer();
                    }
                }
            }
        }
        setStopFlag(true);
        file.close();
    }
}

void SerialThread::clearFixSS(float lati, float loni){
    emit clearFix(lati, loni);
}

void SerialThread::resetTimer()
{
    timeouttimer.setInterval(2000);
    connection = connect(&timeouttimer, &QTimer::timeout, [&]() {
        emit dataStatus(m_gpsTracker.getStatus());
    });
    timeouttimer.start();
    m_gpsTracker.StartTimer();
}
