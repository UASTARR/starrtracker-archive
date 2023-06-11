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

    void parse(QByteArray& data);
    double getLongitude();
    double getLatitude();

private:
    double longitude_;
    double latitude_;

};

#endif // GPSPARSER_H
