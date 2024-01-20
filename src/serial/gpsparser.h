#ifndef GPSPARSER_H
#define GPSPARSER_H

#include <QByteArray>
#include <QObject>
#include <QFile>

class GPSParser : public QObject
{
    Q_OBJECT

public:
    explicit GPSParser(QObject *parent = nullptr);
    ~GPSParser();
    void storeData(const QString &data);
    QStringList parse(QByteArray& data);
    double getLongitude();
    double getLatitude();

private:
    double longitude_;
    double latitude_;

};

#endif // GPSPARSER_H
