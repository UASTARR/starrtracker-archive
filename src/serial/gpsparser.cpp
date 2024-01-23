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
    GpsFormat* parserFormat; // TODO: Figure out a way to do this without the temp
    switch((int)data.at(0).toLatin1())
    {
        case '$': // Indicated TeleGPS dat
        {
            parserFormat = new TeleGPS();
            break;
        }
        case '@': // Indicates Featherweight data
        {
            parserFormat = new Featherweight();
            break;
        }
        default:
            qDebug() << "Unkown Data type" << Qt::endl;
            qDebug() << data << Qt::endl;
            return result;
    }

    QStringList dataStrList = data.split(parserFormat->get_seperator());
    if (sizeof(data)>=8 && dataStrList[parserFormat->get_packet_type_i()] == parserFormat->get_packet())
    {
        result.gps_name = parserFormat->get_name();
        result.latitude = dataStrList[parserFormat->get_lat_i()].toFloat();
        result.longitude = dataStrList[parserFormat->get_long_i()].toFloat();
        result.altitude = dataStrList[parserFormat->get_alt_i()].toFloat();
        result.time = parserFormat->time_format(dataStrList[parserFormat->get_time_i()]);
        result.valid = true;
    }
    else
    {
        qDebug() << "Undesired Data\n" << data <<Qt::endl;
    }
    delete parserFormat;
    return result;
}
