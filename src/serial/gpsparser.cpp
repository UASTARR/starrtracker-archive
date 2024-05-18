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
    if (data.isEmpty())
        return result;
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
            qDebug() << "Unknown Data type" << endl;
            return result;
    }
    qDebug() << data ;
    // Note it will not store the original data. It will store the modified readable data.
    // To store original data, we will have to move it into the switch statement.
    if (storeGPSData) {
        storeData(data, parserFormat->get_name());
    }

    QStringList dataStrList = data.split(parserFormat->get_seperator());
    if (sizeof(data)>=8 && parserFormat->get_packet_type(dataStrList) == parserFormat->get_packet())
    {
        result.gps_name = parserFormat->get_name();
        result.latitude = parserFormat->get_lat(dataStrList);
        result.longitude = parserFormat->get_long(dataStrList);
        result.altitude = parserFormat->get_alt(dataStrList);
//        result.latitude = dataStrList[parserFormat->get_lat_i()].toFloat();
//        result.longitude = dataStrList[parserFormat->get_long_i()].toFloat();
//        result.altitude = dataStrList[parserFormat->get_alt_i()].toFloat();
        result.time = parserFormat->get_time(dataStrList);
        result.valid = true;
    }
    else
    {
        // qDebug() << "Undesired Data\n" << data <<endl;
        result.valid = false;
    }
    delete parserFormat;
    return result;
}

void GPSParser::storeData(const QString &data, const QString &name)
{
    QFile file;
    if (name == Featherweight().get_name()){
        file.setFileName("featherweight_data.txt");
    } else if (name == TeleGPS().get_name()){
        file.setFileName("telegps_data.txt");
    } else {
        file.setFileName("data.txt");
    }
    // Appending parsed data to text file

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

// Still laggy. Some data is bad. Need to check with groundStation.
QString GPSParser::parseTeleGPS(const QString &data)
{
    QStringList tokens = data.split(" ");
    QString modifiedData, reversedData;
    if (tokens[0] == "TELEM"){
        QString oldData = tokens[1];
        for (int i = oldData.length(); i > -1; i-=2){
            reversedData += oldData.midRef(i, 2);
        }
        bool ok = false;
        modifiedData += "TELEM ";

        auto appendNumber = [&](int length, int divisor = 1, char ch = ' ') {
            modifiedData += QString::number(reversedData.rightRef(length).toUInt(&ok, 16) / divisor) + ch;
            reversedData.chop(length);
        };

        int header = reversedData.rightRef(2).toInt(&ok, 16);
        if (header == 34){
            // The following code works but is not code efficient. I have rewritten the code below. Incase that doesn't work
            // comment that and uncomment the below code.

            /* modifiedData.append(QString::number(reversedData.rightRef(2).toInt(&ok, 16)) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(4).toInt(&ok, 16)) + " ");
            reversedData.chop(4);
            modifiedData.append(QString::number(reversedData.rightRef(4).toUInt(&ok, 16) / 100) + " ");
            reversedData.chop(4);
            modifiedData.append(QString::number(reversedData.rightRef(2).toInt(&ok, 16)) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(0x0F && (reversedData.rightRef(2).toUInt(&ok, 16) >> 4))+ " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(4).toInt(&ok, 16)) + " ");
            reversedData.chop(4);
            int32_t decValue = (reversedData.rightRef(8).toLongLong(&ok, 16));
            reversedData.chop(8);
            modifiedData.append(QString::number(decValue / 10.0e6)+ " ");
            decValue = (reversedData.rightRef(8).toLongLong(&ok, 16));
            modifiedData.append(QString::number(decValue / 10.0e6)+ " ");
            reversedData.chop(8);
            int year = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);
            int month = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);
            int day = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);
            int hour = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);
            int min = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);
            int sec = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);
            modifiedData.append(QString::number(day) + "-" + QString::number(month) + "-" + QString::number(year) + " ");
            modifiedData.append(QString::number(hour) + ":" + QString::number(min) + ":" + QString::number(sec) + " ");
            modifiedData.append(QString::number(reversedData.rightRef(2).toUInt(&ok, 16) / 5.0) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(2).toUInt(&ok, 16) / 5.0) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(2).toUInt(&ok, 16) / 5.0) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(2).toUInt(&ok, 16)) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(4).toUInt(&ok, 16)) + " ");
            reversedData.chop(4);
            modifiedData.append(QString::number(reversedData.rightRef(4).toInt(&ok, 16)) + " ");
            reversedData.chop(4);
            modifiedData.append(QString::number(reversedData.rightRef(2).toUInt(&ok, 16)) + " ");
            reversedData.chop(2);
            modifiedData.append(QString::number(reversedData.rightRef(2).toUInt(&ok, 16)));
            reversedData.chop(2); */

            appendNumber(2);
            appendNumber(4);
            appendNumber(4, 100);
            appendNumber(2);
            modifiedData.append(QString::number(0x0F && (reversedData.rightRef(2).toUInt(&ok, 16) >> 4))+ " ");
            reversedData.chop(2);
            appendNumber(4);
            int32_t decValue = (reversedData.rightRef(8).toLongLong(&ok, 16));
            reversedData.chop(8);
            modifiedData.append(QString::number(decValue / 10.0e6)+ " ");
            decValue = (reversedData.rightRef(8).toLongLong(&ok, 16));
            modifiedData.append(QString::number(decValue / 10.0e6)+ " ");
            reversedData.chop(8);
            appendNumber(2, 1, '-');
            appendNumber(2, 1, '-');
            appendNumber(2);
            appendNumber(2, 1, ':');
            appendNumber(2, 1, ':');
            appendNumber(2);
            appendNumber(2, 5);
            appendNumber(2, 5);
            appendNumber(2, 5);
            appendNumber(2);
            appendNumber(4);
            appendNumber(4);
            appendNumber(2);
            appendNumber(2);
        }
    }
    return modifiedData;
}
