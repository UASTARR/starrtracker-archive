#ifndef VALIDGPSFORMATS_H
#define VALIDGPSFORMATS_H

#include <QObject>
#include <QTime>

struct GpsData {
    QString gps_name;
    QTime time;
    QDate date;
    bool valid;
    float latitude; // + for N, - for S
    float longitude; // + for E, - for W
    float altitude;
    int n_sat;
    int n_count_40;
    int n_count_32;
    int n_count_24;
    int rssi;
    float horVelocity;
    float verVelocity;
    float battLevel;
    int pck_rcv;
    int pck_snt;
    qint64 age = 0;
};

struct connectionStatus {
    double time;
    int n_sat;
    int n_count_40;
    int n_count_32;
    int n_count_24;
};

struct GPSFormat {
    virtual QString get_name() = 0;         // GPS Name
    virtual QString get_seperator() = 0;    // data sperator
    virtual QStringList get_packet() = 0;   // Desired packet type
    virtual QList<int> get_size() = 0;             // Desired packet size
    virtual QString get_packet_type(QStringList &data_string) = 0; // Packet type (string)
    virtual int get_packet_size(QStringList &data_string) = 0;     // Packet size (number)
    virtual QTime get_time(QStringList &data_string) = 0;   // Time Elapsed (HH:MM:SS)
    virtual QDate get_date(QStringList &data_string) = 0;   // Date         (YYYY-MM-DD)
    virtual bool get_valid(QStringList &data_string) = 0;   // Valid Data   (Boolean (T / F))
    virtual float get_lat(QStringList &data_string) = 0;    // Latitude     (degrees)
    virtual float get_long(QStringList &data_string) = 0;   // Longitude    (degrees)
    virtual float get_alt(QStringList &data_string) = 0;    // Altitude     (m)
    virtual int get_n_sat(QStringList &data_string) = 0;    // No. of Satellites    (number)
    virtual int get_n_count_40(QStringList &data_string) = 0;   // No. of Satellites with 40db and larger
    virtual int get_n_count_32(QStringList &data_string) = 0;   // No. of Satellites with 32db and larger
    virtual int get_n_count_24(QStringList &data_string) = 0;   // No. of Satellites with 24db and larger
    virtual int get_rssi(QStringList &data_string) = 0;     // RSSI         (-120 dBm to 0 dBm)
    virtual float get_hor_velocity(QStringList &data_string) = 0;  // Horizontal Velocity (Ground Speed)    (m/s)
    virtual float get_ver_velocity(QStringList &data_string) = 0;  // Vertical Velocity (Air Speed)         (m/s)
    virtual int get_direction(QStringList &data_string) = 0;       // Direction     (degrees)
    virtual float get_batt_level(QStringList &data_string) = 0;    // Battery Level Indication  (Volts)
    virtual int get_pck_rcv(QStringList &data_string) = 0;  // Number of Successful Telemetry Packets Received (number)
    virtual int get_pck_snt(QStringList &data_string) = 0;  // Number of Successful Telemetry Packets Sent     (number)
    virtual ~GPSFormat() = default;
};

struct Featherweight : public GPSFormat {
    QString get_name() override {
        return "Featherweight";
    }
    QString get_seperator() override {
        return " ";
    }
    QStringList get_packet() override {
        return {"GPS_STAT", "RX_NOMTK", "BATT_BLE"};
    }
    QList<int> get_size() override {
        return {200, 64};
    }
    int get_packet_size(QStringList &data_string) override{
        return data_string[2].toInt();
    }
    QString get_packet_type(QStringList &data_string) override {
        return data_string[1];
    }
    QDate get_date(QStringList &data_string) override {
        QDateTime date;
        date = date.addYears(data_string[3].toInt())
                   .addMonths(data_string[4].toInt())
                   .addDays(data_string[5].toInt());
        return date.date();
    }
    QTime get_time(QStringList &data_string) override {
        return QTime::fromString(data_string[6]);
    }
    bool get_valid(QStringList &data_string) override {
        return (data_string[7] == "CRC_OK") ? 1 : 0;
    }
    float get_alt(QStringList &data_string) override {
        return data_string[11].toFloat() * 0.3048;
    }
    float get_lat(QStringList &data_string) override {
        return data_string[13].toFloat();
    }
    float get_long(QStringList &data_string) override {
        return data_string[15].toFloat();
    }
    float get_hor_velocity(QStringList &data_string) override {
        return data_string[17].toFloat() * 0.3048;
    }
    int get_direction(QStringList &data_string) override {
        return data_string[18].toInt();
    }
    float get_ver_velocity(QStringList &data_string) override {
        return data_string[19].toFloat() * 0.3048;
    }
    int get_n_sat(QStringList &data_string) override{
        return data_string[23].toInt();
    }
    int get_n_count_40(QStringList &data_string) override {
        return data_string[26].toInt();
    }
    int get_n_count_32(QStringList &data_string) override {
        return data_string[25].toInt();
    }
    int get_n_count_24(QStringList &data_string) override {
        return data_string[24].toInt();
    }
    int get_rssi(QStringList &data_string) override {
        return data_string[16].toInt();
    }
    float get_batt_level(QStringList &data_string) override {
        return data_string[7].toFloat() / 1000;
    }
    int get_pck_rcv(QStringList &data_string) override {
        return data_string[12].toInt();
    }
    int get_pck_snt(QStringList &data_string) override {
        return data_string[14].toInt();
    }

};

struct TeleGPS : public GPSFormat {
    QString get_name() override {
        return "TeleGPS";
    }
    QString get_seperator() override {
        return " ";
    }
    QStringList get_packet() override {
        return {"5", "6"};
    }
    QList<int> get_size() override {
        return {32};
    }
    int get_packet_size(QStringList &data_string) override{
        return data_string[1].toInt();
    }
    QString get_packet_type(QStringList &data_string) override {
        return data_string[4];
    }
    QDate get_date(QStringList &data_string) override {
        return QDate::fromString(data_string[13], "yy-MM-dd");
    }
    QTime get_time(QStringList &data_string) override {
        QTime a(0,0,0);
        a = a.addSecs(data_string[3].toInt());
        return a;
    }
    bool get_valid(QStringList &data_string) override {
        return data_string[6].toInt();
    }
    float get_alt(QStringList &data_string) override {
        return data_string[10].toFloat();
    }
    float get_lat(QStringList &data_string) override {
        return data_string[11].toFloat();
    }
    float get_long(QStringList &data_string) override {
        return data_string[12].toFloat();
    }
    float get_hor_velocity(QStringList &data_string) override {
        return data_string[19].toFloat();
    }
    int get_direction(QStringList &data_string) override {
        return data_string[21].toInt();
    }
    float get_ver_velocity(QStringList &data_string) override {
        return data_string[20].toFloat();
    }
    int get_n_sat(QStringList &data_string) override{
        return data_string[5].toInt();
    }
    int get_n_count_40(QStringList &data_string) override {
        return data_string[6].toInt();
    }
    int get_n_count_32(QStringList &data_string) override {
        return data_string[7].toInt();
    }
    int get_n_count_24(QStringList &data_string) override {
        return data_string[8].toInt();
    }
    int get_rssi(QStringList &data_string) override {
        // return data_string[23].toInt();
        return data_string[23].toInt() / 2 - 74;
    }
    float get_batt_level(QStringList &data_string) override {
        return 0;
    }
    int get_pck_rcv(QStringList &data_string) override {
        return 0;
    }
    int get_pck_snt(QStringList &data_string) override {
        return 0;
    }
};

#endif // VALIDGPSFORMATS_H
