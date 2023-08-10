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

    void startSerialThread(const QString &port);
    void stopSerialThread();

signals:
    void error(const QString &s);

private:
    void run() override;
    QMutex m_mutex;
    bool m_quit = false;
    bool checkForQuitFlag();
    GPSParser m_gpsTracker;
    QString m_port;
};

#endif // SERIALTHREAD_H