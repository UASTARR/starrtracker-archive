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

QStringList GPSParser::parse(QByteArray &data)
{
    QString text;
    QString gpsType;
    QStringList result; // [0] = GPS type, [1] = gps data
    if (sizeof(data)>=8 && data[0] == '$')
    {
        result.append("TeleGPS");
        QString dataString = QString::fromLocal8Bit(data);
        QStringList strs = dataString.split(',');

        qDebug() << strs << Qt::endl;

        if (strs[0] == "$GPGGA" || strs[0] == "$GNGGA")
        {
//            result.append(tr("Time: %1\nLatitude: %2 %3\nLongitude: %4 %5\nFix Quality: %6\nSatillites Used: %7\n\n").arg(strs[1],strs[2],strs[3],strs[4],strs[5],strs[6],strs[7]));
            for (int i = 1; i <= 7; i++){
                result.append(strs[i]);
            }
//            result[1] = static_cast<double>(result[1].toFloat()/100);       // To check if it divides by 100
//            result[3] = static_cast<double>(result[3].toFloat()/100);
            result[1] = result[1].toFloat() / 100;
            result[3] = result[3].toFloat() / 100;
            result.append(strs[9]);     // Altitude
            result.append("m");         // Altitude unit

            qDebug() << result[1] << " " << result[2] << " " << result[4] << " " << result[9] << Qt::endl;

        }
    }
    else if (sizeof(data)>=8 && data[0] == '@')
    {
        result.append("Featherweight");
        QString dataString = QString::fromLocal8Bit(data);
        QStringList strs = dataString.split(' ');

        qDebug() << strs << Qt::endl;

        if (strs[1] == "GPS_STAT")
        {
            result.append(strs[6]);     // Time
            if (strs[14] > 0){          // Latitude
                result.append(strs[14]);
                result.append("N");
            } else {
                result.append("-" + strs[14]);
                result.append("S");
            }

            if (strs[16] > 0){          // Longitude
                result.append(strs[16]);
                result.append("E");
            } else {
                result.append("-" + strs[16]);
                result.append("W");
            }

            result.append(strs[12]);    // Altitude
            result.append("feet");

            qDebug() << result[1] << " " << result[2] << " " << result[4] << " " << result[9] << Qt::endl;
        }
    }
    else
    {
        QTextStream(stdout) <<  tr("Can't parse data\n");
    }

    return result;
}
