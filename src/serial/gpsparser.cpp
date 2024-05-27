#include "gpsparser.h"

GPSParser::GPSParser(QObject *parent) : QObject(parent), data(new GpsData()) {
    QString filename = "GPSData.txt";
    int count = 0;
    while (QFile::exists(filename)) {
        filename = QString("GPSData_%1.txt").arg(count++);
    }
    file.setFileName(filename);
}

GPSParser::~GPSParser() {
    delete data;
}

QString GPSParser::getGpsName(){
    return data->gps_name;
}

bool GPSParser::validateData() const{
    qDebug() << data->gps_name << data->time << data->latitude << data->longitude << data->altitude << data->rssi;
    // Check if gps_name is empty
    if (data->gps_name.isEmpty()) {
        return false;
    }

    // Check if time is valid
    if (!data->time.isValid()) {
        return false;
    }

    // Check if latitude is within valid range
    if (data->latitude < -90.0f || data->latitude > 90.0f) {
        return false;
    }

    // Check if longitude is within valid range
    if (data->longitude < -180.0f || data->longitude > 180.0f) {
        return false;
    }

    // Check if altitude is a reasonable value (can be negative for below sea level)
    // For simplicity, we'll assume altitude must be between -500 and 70000 meters
    if (data->altitude < -500.0f || data->altitude > 70000.0f) {
        return false;
    }

    // Check if rssi (signal strength) is within a plausible range
    // Assuming RSSI is in dBm, which typically ranges from -120 dBm to 0 dBm
    if (data->rssi < -120 || data->rssi > 0) {
        return false;
    }

    // Check if n_sat (number of satellites) is non-negative
    // if (data->n_sat < 0) {
    //     return false;
    // }



    // Check if horizontal and vertical velocities are non-negative
    // For simplicity, assuming velocities must be between 0 and 500 m/s
    // if (data->horVelocity < 0.0f || data->horVelocity > 1000.0f) {
    //     return false;
    // }

    // if (data->verVelocity < 0.0f || data->verVelocity > 1000.0f) {
    //     return false;
    // }

    // All checks passed
    return true;
}

void GPSParser::clearData() const{
    data->gps_name.clear();
    data->time = QTime();
    data->latitude = -100.0f;
    data->longitude = -200.0f;
    data->altitude = -1000.0f;
    data->n_sat = -1;
    data->horVelocity = -1.0f;
    data->verVelocity = -1.0f;
    data->date = QDate();
    data->battLevel = -1;
    data->pck_rcv = -1;
    data->pck_snt = -1;
}

void GPSParser::storeData(QString &dataToStore){
    if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);

        if (file.size() == 0) {
            QDateTime currentDateTime = QDateTime::currentDateTime();
            stream << data->gps_name << Qt::endl;
            stream << currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        }

        stream << dataToStore << Qt::endl;
        file.close();
    } else {
        QTextStream(stdout) << tr("Error opening the file for writing\n");
    }
}

GpsData GPSParser::getData(){
    return *data;
}

void GPSParser::parse(QString &newdata, bool &storeGPSData){
    if (!newdata.isEmpty()){
        // Telegps
        if (newdata.startsWith("TELEM")){
            TeleGPS *parserformat = new TeleGPS();
            newdata = parseTeleGPS(newdata);
            QStringList dataStrList = newdata.split(parserformat->get_seperator());
            if (parserformat->get_packet_type(dataStrList) == parserformat->get_packet().at(0) &&
                parserformat->get_packet_size(dataStrList) >= parserformat->get_size().at(0)){
                data->gps_name = parserformat->get_name();
                data->time = parserformat->get_time(dataStrList);
                data->date = parserformat->get_date(dataStrList);

                data->latitude = parserformat->get_lat(dataStrList);
                data->longitude = parserformat->get_long(dataStrList);
                data->altitude = parserformat->get_alt(dataStrList);
                data->horVelocity = parserformat->get_hor_velocity(dataStrList);
                data->verVelocity = parserformat->get_ver_velocity(dataStrList);

                data->n_sat = parserformat->get_n_sat(dataStrList);
                data->rssi = parserformat->get_rssi(dataStrList);
            }
            delete parserformat;
        } // Featherweight
        else if (newdata.startsWith("@")){
            Featherweight *parserformat = new Featherweight();
            QStringList dataStrList = newdata.split(parserformat->get_seperator());
            for (int i = 0; i < dataStrList.size(); ++i) {
                if (dataStrList.at(i).isEmpty()) {
                    dataStrList.removeAt(i);
                    --i; // Decrement the index to adjust for the removed element
                }
            }
            if (parserformat->get_packet_type(dataStrList) == parserformat->get_packet().at(0) &&
                parserformat->get_packet_size(dataStrList) >= parserformat->get_size().at(0)){
                data->gps_name = parserformat->get_name();
                data->time = parserformat->get_time(dataStrList);
                data->date = parserformat->get_date(dataStrList);

                data->latitude = parserformat->get_lat(dataStrList);
                data->longitude = parserformat->get_long(dataStrList);
                data->altitude = parserformat->get_alt(dataStrList);
                data->horVelocity = parserformat->get_hor_velocity(dataStrList);
                data->verVelocity = parserformat->get_ver_velocity(dataStrList);

                data->n_sat = parserformat->get_n_sat(dataStrList);
            }
            else if (parserformat->get_packet_type(dataStrList) == parserformat->get_packet().at(1) &&
                     parserformat->get_packet_size(dataStrList) >= parserformat->get_size().at(0)){
                data->rssi = parserformat->get_rssi(dataStrList);
                data->pck_rcv = parserformat->get_pck_rcv(dataStrList);
                data->pck_snt = parserformat->get_pck_snt(dataStrList);
            } else if (parserformat->get_packet_type(dataStrList) == parserformat->get_packet().at(2) &&
                       parserformat->get_packet_size(dataStrList) >= parserformat->get_size().at(1)){
                data->battLevel = parserformat->get_batt_level(dataStrList);
            }
            delete parserformat;
        }

        if (storeGPSData){
            storeData(newdata);
        }
    }
}

// String Format
// TELEM Packetlength SerialNumber DeviceTime PacketType no.ofSats valid running dateValid courseValid altitude latitude longitude date time pdop hdop vdop mode horVelocity verVelocity courseDirection rssi lqi checksum
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
            appendNumber(2);
            appendNumber(4);
            appendNumber(4, 100);
            appendNumber(2);
            int flags = reversedData.rightRef(2).toUInt(&ok, 16);
            reversedData.chop(2);

            // Parse each flag bit
            int nsats = flags & 0x0F;
            bool valid = (flags >> 4) & 0x01;
            bool running = (flags >> 5) & 0x01;
            bool date_valid = (flags >> 6) & 0x01;
            bool course_valid = (flags >> 7) & 0x01;

            // Append each flag to the modifiedData string
            modifiedData.append(QString::number(nsats) + " ");
            modifiedData.append(QString::number(valid) + " ");
            modifiedData.append(QString::number(running) + " ");
            modifiedData.append(QString::number(date_valid) + " ");
            modifiedData.append(QString::number(course_valid) + " ");

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
            appendNumber(4, 100);
            appendNumber(4, 100);
            modifiedData += QString::number(reversedData.rightRef(2).toUInt(&ok, 16) * 2) + ' ';
            reversedData.chop(2);
            appendNumber(2);
            appendNumber(2);
            appendNumber(2);
            appendNumber(2);
        }
    }
    return modifiedData;
}

void GPSParser::StartTimer(){
    data->age = 0;
    elapsedTime.start();
}

status GPSParser::getStatus(){
    status connectionStatus;
    if (elapsedTime.isValid())
        data->age = elapsedTime.elapsed() / 1000;
    connectionStatus.age = data->age;
    connectionStatus.rssi = data->rssi;
    return connectionStatus;
}


