#include "gpsparser.h"
#include <iostream>
#include <QTextStream>

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
        if (strs[0] == "$GPGGA" || strs[0] == "$GNGGA")
        {
             QString parsedData = tr("Time: %1\nLattitude: %2 %3\nLongitude: %4 %5\nFix Quality: %6\nSatellites Used: %7\n\n")
                .arg(strs[1], strs[2], strs[3], strs[4], strs[5], strs[6], strs[7]);

            result.append(parsedData);
            storeData(parsedData);
        }
    }
    else if (sizeof(data)>=8 && data[0] == '@')
    {
        result.append("Featherweight");
        QString dataString = QString::fromLocal8Bit(data);
        QStringList strs = dataString.split(' ');
        if (strs[1] == "GPS_STAT")
        {
            QString parsedData = tr("Time: %1\nLattitude: %2\nLongitude: %3\nSatellites Used: %4\n\n")
                .arg(strs[6], strs[14], strs[16], strs[24]);

            result.append(parsedData);
            storeData(parsedData);
        }
    }
    else
    {
        QTextStream(stdout) <<  tr("Can't parse data\n");
    }

    return result;
}

void GPSParser::storeData(const QString &data)
{
    // Appending parsed data to text file
    QFile file("gps_data.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << data << endl;
        file.close();
    }
    else
    {
        QTextStream(stdout) << tr("Error opening the file for writing\n");
    }
}
