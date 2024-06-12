#ifndef GPSPARSER_H
#define GPSPARSER_H

#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QObject>
#include <QTime>
#include <QDateTime>
#include <QCoreApplication>
#include <QElapsedTimer>
#include "validgpsformats.h"

class GPSParser : public QObject
{
    Q_OBJECT

public:
    explicit GPSParser(QObject *parent = nullptr);
    ~GPSParser();
    void storeData(QString &rawData, QString &parsedData);
    bool validateData();
    QString getGpsName();
    void clearData() const;
    GpsData getData();
    void parse(QString &rawdata, bool &storeGPSData);
    void StartTimer();
    connectionStatus getStatus();

public slots:
    void clearFix(float lati, float loni);

private:
    GpsData *data;
    QFile file_raw;
    QFile file_parsed;
    QElapsedTimer elapsedTime;
    QString parseTeleGPS(const QString &data);
    float latFix = 0, lonFix = 0;
};

#endif // GPSPARSER_H
