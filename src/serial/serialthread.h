#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <QMutex>
#include "gpsparser.h"

class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QObject *parent = nullptr);
    ~SerialThread();

    void startSerialThread(const QString &port, const qint32 &baud);
    void stopSerialThread();

signals:
    void dataReady(const QStringList &data);
    void error(const QString &s);

private:
    void run() override;

    QMutex m_mutex;
    bool m_stop;
    void setStopFlag(bool newState);
    bool getStopFlag();
    QString m_port;
    QString getPort();
    qint32 m_baud;
    qint32 getBaud();
    GPSParser m_gpsTracker;
};

#endif // SERIALTHREAD_H
