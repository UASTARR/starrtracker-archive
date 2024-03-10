#ifndef VALIDGPSFORMATS_H
#define VALIDGPSFORMATS_H

#include <QObject>
#include <QTime>
#include <iostream>

//  GPS Data displayed to the user
struct GpsData {
    bool valid = false; // Valid data packet check
    QString gps_name;
    QTime time;
    float latitude; // + for N, - for S
    float longitude; // + for E, - for W
    float altitude;
};

// Abstract struct for representing gps data formats.
// All new formats must overload each value and function
struct GpsFormat {
    virtual QString get_name() = 0; // Name of GPS tracker
    virtual QString get_seperator() = 0; // data sperator
    virtual QString get_packet() = 0; // Desired packet type
    virtual int get_packet_type_i() = 0; // Packet type index
    virtual int get_time_i() = 0; // Time index
    virtual int get_lat_i() = 0; // Latitude index
    virtual int get_long_i() = 0; // Longitude index
    virtual int get_alt_i() = 0; // Altitude index
    virtual QTime time_format(QString &time_data) = 0; // Parses string version of time data into a QTime object

    virtual ~GpsFormat() = default; // Virtual deconstructor
};

struct Featherweight : public GpsFormat {
    QString get_name() override {
        return "Featherweight";
    }
    QString get_seperator() override {
        return " ";
    }
    QString get_packet() override {
        return "GPS_STAT";
    }
    int get_packet_type_i() override {
        return 1;
    }
    int get_time_i() override  {
        return  6;
    }
    int get_lat_i() override {
        return 14;
    }
    int get_long_i() override {
        return 16;
    }
    int get_alt_i() override {
        return 12;
    }
    QTime time_format(QString &time_data) override {
        return QTime::fromString(time_data);
    };
};

struct TeleGPS : public GpsFormat {
    QString get_name() override {
        return "TeleGPS";
    }
    QString get_seperator() override {
        return ",";
    }
    QString get_packet() override {
        return "TELEM";
    }
    int get_packet_type_i() override {
        return 0;
    }
    int get_time_i() override  {
        return 9;
    }
    int get_lat_i() override {
        return 7;
    }
    int get_long_i() override {
        return 8;
    }
    int get_alt_i() override {
        return 6;
    }
    QTime time_format(QString &time_data) override {
        return QTime::fromString(time_data);
    };
};

#endif // VALIDGPSFORMATS_H
