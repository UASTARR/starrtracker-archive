#include "gpsparser.h"

GPSParser::GPSParser(QObject *parent) : QObject(parent)
{

}

GPSParser::~GPSParser()
{

}

GpsData GPSParser::parse(QString &data, bool &storeGPSData)
{
    GpsData result;
    TeleGPS temp = TeleGPS();
    GpsFormat* parserFormat; // TODO: Figure out a way to do this without the temp
    switch((int)data.at(0).toLatin1())
    {
        case 'T': // Indicated TeleGPS dat
        {
            parserFormat = new TeleGPS();
            // TODO: This checks for T not TELEM. So an empty string might get added to the file
            data = parseTeleGPS(data);
            break;
        }
        case '@': // Indicates Featherweight data
        {
            parserFormat = new Featherweight();
            break;
        }
        default:
            qDebug() << "Unkown Data type" << Qt::endl;
            return result;
    }
    qDebug() << data ;
    // Note it will not store the original data. It will store the modified readable data.
    // To store original data, we will have to move it into the switch statement.
    if (storeGPSData) {
        storeData(data);
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

void GPSParser::storeData(const QString &data)
{
    // Appending parsed data to text file
    QFile file("gps_data.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << data << Qt::endl;
        file.close();
    }
    else
    {
        QTextStream(stdout) << tr("Error opening the file for writing\n");
    }
}

// Still laggy. Some data is bad. Need to check with groundStation.
QString GPSParser::parseTeleGPS(QString &data)
{
    QString type = data.split(" ")[0];
    QString modifiedString, reverseData;
    if (type == "TELEM"){
        data = data.split(" ")[1];

        QList<int> splits;
        bool ok = false;

        splits << 2 << 4 << 4 << 2 << 2 << 4 << 8 << 8;

        for (int i = data.length(); i > -1; i-=2){
            reverseData += data.mid(i, 2);
        }
        reverseData = reverseData.right(reverseData.length() - 26);

        modifiedString += "TELEM,";
        for (const int i : splits){
            QString temp = QString::number(reverseData.right(i).toUInt(&ok, 16));
            if (ok){
                modifiedString.append(temp + ",");
            } else {
                return "";
            }

            reverseData.chop(i);
        }

        // Time: I think refers to the current time. Not time elapsed since device start.
        QString temp1 = QString::number(reverseData.left(2).toUInt(&ok, 16));
        QString temp2 = QString::number(reverseData.mid(2,2).toUInt(&ok, 16));
        QString temp3 = QString("%1").arg(reverseData.mid(4, 2).toUInt(&ok, 16), 2, 10, QChar('0'));;
        if (ok){
            modifiedString.append(QString("%1:%2:%3.000").arg(temp3, temp2, temp1));
        }
    }
    return modifiedString;
}
