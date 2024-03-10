#ifndef GPSPARSER_H
#define GPSPARSER_H

#include "validgpsformats.h"
#include <QFile>
#include <QByteArray>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>

class GPSParser : public QObject
{
    Q_OBJECT

public:
    explicit GPSParser(QObject *parent = nullptr);
    ~GPSParser();

//    struct GpsData {
//        QString gps_type;
//        float time_s;
//        float time_m;
//        float time_h;
//        float latitude; // + 'for N, - for S
//        float longitude; // + for E, - for W
//        float altitude;
//    };

    GpsData parse(QString &data, bool &storeGPSData);
    void storeData(const QString &data);

    double getLongitude();
    double getLatitude();

private:
    double longitude_;
    double latitude_;

    const QStringList GPS_TYPES_ACCEPTED = {"Featherweight", "TeleGPS"};

    QString parseTeleGPS(QString &data);
};

#endif // GPSPARSER_H
