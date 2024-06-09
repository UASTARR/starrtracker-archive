#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QMutex>
#include <QSerialPort>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include "gpsparser.h"

class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QObject *parent = nullptr);
    ~SerialThread();

    void startLocalDataThread(const QString &file);
    void startSerialDataThread(const QString &port, const qint32 &baud, const bool &saveData);
    void stopSerialThread();
    void resetTimer();

public slots:
    void clearFixSS(float lati, float loni);

signals:
    void dataReady(const GpsData &data);
    void error(const QString &s);
    void dataStatus(const connectionStatus status);
    void appendData(const QString &data, const QString &color);
    void clearFix(float, float);

private:
    void run() override;
    QMutex m_mutex;
    bool m_serial_mode;
    bool m_stop;
    bool m_save_data;
    void setStopFlag(bool newState);
    bool getStopFlag();
    QString m_port;
    QString getPort();
    qint32 m_baud;
    qint32 getBaud();
    QString m_file;
    QString getFile();
    GPSParser m_gpsTracker;
    QTimer timeouttimer;
    QMetaObject::Connection connection;
    unsigned long time = 5000;
};

#endif // SERIALTHREAD_H

