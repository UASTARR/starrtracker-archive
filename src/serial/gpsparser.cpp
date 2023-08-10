#include "gpsparser.h"
#include <iostream>
#include <QTextStream>

GPSParser::GPSParser(QObject *parent) : QObject(parent)
{

}

GPSParser::~GPSParser()
{

}

void GPSParser::parse(QByteArray &data)
{
    if (sizeof(data)>=6 && data[0] == '$')
    {
        QString dataString = QString::fromLocal8Bit(data);
        QStringList strs = dataString.split(',');
        if (strs[0] == "$GPGGA" || strs[0] == "$GNGGA")
        {
            QTextStream(stdout) << tr("Time: %1\nLattitude: %2 %3\nLongitude: %4 %5\nFix Quality: %6\nSatillites Used: %7\n\n").arg(strs[1],strs[2],strs[3],strs[4],strs[5],strs[6],strs[7]);

        }
    }
    else
    {
        QTextStream(stdout) <<  tr("Can't parse data\n");
    }
}
