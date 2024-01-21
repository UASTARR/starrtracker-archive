#include "gpsparser.h"
#include <iostream>
#include <QTextStream>
#include <QDebug>
GPSParser::GPSParser(QObject *parent) : QObject(parent)
{

}

GPSParser::~GPSParser()
{

}

GpsData GPSParser::parse(QString &data)
{
    GpsData result;
    TeleGPS temp = TeleGPS();
    GpsFormat& parserFormat = temp; // TODO: Figure out a way to do this without the temp
    switch((int)data.at(0).toLatin1())
    {
        case '$': // Indicated TeleGPS dat
        {
            parserFormat = TeleGPS();
            break;
        }
        case '@': // Indicates Featherweight data
        {
            parserFormat = Featherweight();
            break;
        }
        default:
            qDebug() << "Unkown Data type" << Qt::endl;
            qDebug() << data << Qt::endl;
    }

//    QString tempStr = QString::fromLocal8Bit(data);
    QStringList dataStrList = data.split(parserFormat.seperator);
    if (sizeof(data)>=8 && dataStrList[parserFormat.packet_type_i] == parserFormat.packet)
    {
        result.gps_name = parserFormat.name;
        result.latitude = dataStrList[parserFormat.lat_i].toFloat();
        result.longitude = dataStrList[parserFormat.long_i].toFloat();
        result.altitude = dataStrList[parserFormat.alt_i].toFloat();
        result.time = parserFormat.time_format(dataStrList[parserFormat.time_i]);
        result.valid = true;
    }
    else
    {
        qDebug() << "Undesired Data" << Qt::endl;
    }
    return result;
}
