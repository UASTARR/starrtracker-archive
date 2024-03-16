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
    virtual QString get_packet_type(QStringList &data_string) = 0; // Packet type index
    virtual float get_lat(QStringList &data_string) = 0;
    virtual float get_long(QStringList &data_string) = 0;
    virtual float get_alt(QStringList &data_string) = 0;
//    virtual int get_time_i() = 0; // Time index
//    virtual int get_lat_i() = 0; // Latitude index
//    virtual int get_long_i() = 0; // Longitude index
//    virtual int get_alt_i() = 0; // Altitude index
    virtual QTime get_time(QStringList &data_string) = 0; // Parses string version of time data into a QTime object

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
    QString get_packet_type(QStringList &data_string) override {
        return data_string[14];
    }
//    int get_time_i() override  {
//        return  6;
//    }
//    int get_lat_i() override {
//        return 14;
//    }
//    int get_long_i() override {
//        return 16;
//    }
//    int get_alt_i() override {
//        return 12;
//    }
    float get_lat(QStringList &data_string) override {
        return data_string[14].toFloat();
    }
    float get_long(QStringList &data_string) override {
        return data_string[16].toFloat();
    }
    float get_alt(QStringList &data_string) override {
        return data_string[12].toFloat();
    }
    QTime get_time(QStringList &data_string) override {
        return QTime::fromString(data_string[6]);
    }
};

struct TeleGPS : public GpsFormat {
    QString get_name() override {
        return "TeleGPS";
    }
    QString get_seperator() override {
        return ",";
    }
    QString get_packet() override {
        return "5";
    }
    QString get_packet_type(QStringList &data_string) override {
        return data_string[4];
    }
    //    int get_time_i() override  {
    //        return 9;
    //    }
    //    int get_lat_i() override {
    //        return 7;
    //    }
    //    int get_long_i() override {
    //        return 8;
    //    }
    //    int get_alt_i() override {
    //        return 6;
    //    }
    float get_lat(QStringList &data_string) override {
        return data_string[7].toFloat() / 107.0;         // Extracting the latitude -> Requires division by 107
    };
    float get_long(QStringList &data_string) override {
        return data_string[8].toFloat() / 107.0;         // Extracting the latitude -> Requires division by 107
    };
    float get_alt(QStringList &data_string) override {
        return data_string[6].toFloat();
    };
    QTime get_time(QStringList &data_string) override {
        return QTime::fromString(data_string[9]);
    };
};

#endif // VALIDGPSFORMATS_H
