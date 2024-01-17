#ifndef VALIDGPSFORMATS_H
#define VALIDGPSFORMATS_H

#include <QObject>
#include <QTime>
#include <iostream>

//  GPS Data displayed to the user
struct GpsData {
    QString gps_name;
    QTime time;
    float latitude; // + 'for N, - for S
    float longitude; // + for E, - for W
    float altitude;
};

struct GpsFormat {
    virtual QTime time_format(QString &time_data) = 0;
};

struct Featherweight : GpsFormat {
    const QString name = "Featherweight";
    const QString seperator = " ";
    const int packet_type_i = 1;
    const int time_i = 6;
    const int lat_i = 0;
    const int long_i = 0;
    const int alt_i = 0;
    QTime time_format(QString &time_data) override {
        return QTime::fromString(time_data);
    };
};

struct TeleGPS : GpsFormat {
    const QString name = "TeleGPS";
    const QString seperator = ",";
    const int packet_type_i = 0;
    const int time_i = 1;
    const int lat_i = 2;
    const int long_i = 4;
    const int alt_i = 9;
    QTime time_format(QString &time_data) override {
        QString reformat = QString("%1:%2:%3").arg(time_data.left(2), time_data.mid(2,2), time_data.right(6));
        return QTime::fromString(reformat);
    }
};

#endif // VALIDGPSFORMATS_H
