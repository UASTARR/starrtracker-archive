#ifndef GPSPARSER_H
#define GPSPARSER_H

#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QObject>
#include <QTime>
#include <QDateTime>
#include <QCoreApplication>
#include <QElapsedTimer>
#include "validgpsformats.h"

class GPSParser : public QObject
{
    Q_OBJECT

public:
    explicit GPSParser(QObject *parent = nullptr);
    ~GPSParser();
    QStringList parse(QByteArray& data);
    double getLongitude();
    double getLatitude();

private:
    double longitude_;
    double latitude_;
    void storeData(QString &dataToStore);
    bool validateData() const;
    QString getGpsName();
    void clearData() const;
    GpsData getData();
    void parse(QString &newdata, bool &storeGPSData);
    void StartTimer();
    status getStatus();

private:
    GpsData *data;
    QFile file;
    QElapsedTimer elapsedTime;
    QString parseTeleGPS(const QString &data);

signals:
};

#endif // GPSPARSER_H
