#ifndef GPSPARSER_H
#define GPSPARSER_H

#include <QByteArray>
#include <QObject>

class GPSParser : public QObject
{
    Q_OBJECT

public:
    explicit GPSParser(QObject *parent = nullptr);
    ~GPSParser();

    QStringList parse(QByteArray& data);
    double getLongitude();
    double getLatitude();
    struct GpsData {
        float time;
        float latitude;
        float longitude;
        float altitude;
    };

private:
    double longitude_;
    double latitude_;

};

#endif // GPSPARSER_H
