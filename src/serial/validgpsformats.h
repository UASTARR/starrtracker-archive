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
    QString name = "UNKNOWN"; // Name of GPS tracker
    QString seperator = ""; // data sperator
    QString packet = ""; // Desired packet type
    int packet_type_i = 0; // Packet type index
    int time_i = 0; // Time index
    int lat_i = 0; // Latitude index
    int long_i = 0; // Longitude index
     int alt_i = 0; // Altitude index
    virtual QTime time_format(QString &time_data) = 0; // Parses string version of time data into a QTime object
};

struct Featherweight : GpsFormat {
    QString name = "Featherweight";
    QString seperator = " ";
    QString packet = "";
    int packet_type_i = 1;
    int time_i = 6;
    int lat_i = 0;
    int long_i = 0;
    int alt_i = 0;
    QTime time_format(QString &time_data) override {
        return QTime::fromString(time_data);
    };
};

struct TeleGPS : GpsFormat {
    QString name = "TeleGPS";
    QString seperator = ",";
    QString packet = "";
    int packet_type_i = 0;
    int time_i = 1;
    int lat_i = 2;
    int long_i = 4;
    int alt_i = 9;
    QTime time_format(QString &time_data) override {
        QString reformat = QString("%1:%2:%3").arg(time_data.left(2), time_data.mid(2,2), time_data.right(6));
        return QTime::fromString(reformat);
    }
};

#endif // VALIDGPSFORMATS_H
