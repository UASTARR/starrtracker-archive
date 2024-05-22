#ifndef GPSPARSER_H
#define GPSPARSER_H

#include "validgpsformats.h"
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>

class GPSParser : public QObject
{
    Q_OBJECT

public:
    explicit GPSParser(QObject *parent = nullptr);
    ~GPSParser();
    GpsData parse(QString &data, bool &storeGPSData);
    void storeData(const QString &data, const QString &name);
    double getLongitude();
    double getLatitude();

private:
    double longitude_;
    double latitude_;
    const QStringList GPS_TYPES_ACCEPTED = {"Featherweight", "TeleGPS"};
    QString parseTeleGPS(const QString &data);
};

#endif // GPSPARSER_H
