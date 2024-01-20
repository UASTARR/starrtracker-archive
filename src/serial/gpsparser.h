#ifndef GPSPARSER_H
#define GPSPARSER_H

#include <QByteArray>
#include "validgpsformats.h"

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

    GpsData parse(QByteArray& data);

    double getLongitude();
    double getLatitude();

private:
    double longitude_;
    double latitude_;

    const QStringList GPS_TYPES_ACCEPTED = {"Featherweight", "TeleGPS"};

};

#endif // GPSPARSER_H
