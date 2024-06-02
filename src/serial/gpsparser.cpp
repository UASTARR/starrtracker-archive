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
    // if (data->rssi < -120 || data->rssi > -1) {
    //     return false;
    // }

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
            if (dataStrList.length() > 5){
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
                } else if (parserformat->get_packet_type(dataStrList) == parserformat->get_packet().at(1) &&
                           parserformat->get_packet_size(dataStrList) >= parserformat->get_size().at(0)){
                    data->n_sat = parserformat->get_n_sat(dataStrList);
                    data->n_count_40 = parserformat->get_n_count_40(dataStrList);
                    data->n_count_32 = parserformat->get_n_count_32(dataStrList);
                    data->n_count_24 = parserformat->get_n_count_24(dataStrList);
                }
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
            if (dataStrList.length() > 2){
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
                    data->n_count_40 = parserformat->get_n_count_40(dataStrList);
                    data->n_count_32 = parserformat->get_n_count_32(dataStrList);
                    data->n_count_24 = parserformat->get_n_count_24(dataStrList);
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
            }

            delete parserformat;
        }

        if (storeGPSData){
            storeData(newdata);
        }
    }
}

// String Format
// TELEM Packetlength SerialNumber DeviceTime PacketType no.ofSats valid running dateValid courseValid altitude latitude longitude date time pdop hdop vdop mode horVelocity verVelocity courseDirection unused rssi lqi checksum
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
        qDebug() << reversedData;
        auto appendNumber = [&](int length, int divisor = 1, char ch = ' ') {
            modifiedData += QString::number(reversedData.rightRef(length).toUInt(&ok, 16) / divisor) + ch;
            reversedData.chop(length);
        };

        int header = reversedData.rightRef(2).toInt(&ok, 16);
        if (header == 34){
            appendNumber(2);
            appendNumber(4);
            appendNumber(4, 100);
            int packetType = reversedData.rightRef(2).toInt(&ok, 16);
            appendNumber(2);

            if (packetType == 5){
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

                int16_t intShort = (reversedData.rightRef(4).toInt(&ok, 16));
                reversedData.chop(4);
                modifiedData.append(QString::number(intShort)+ " ");
                int32_t intLong = (reversedData.rightRef(8).toLongLong(&ok, 16));
                reversedData.chop(8);
                modifiedData.append(QString::number(intLong / 10.0e6)+ " ");
                intLong = (reversedData.rightRef(8).toLongLong(&ok, 16));
                modifiedData.append(QString::number(intLong / 10.0e6)+ " ");
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
                intShort = reversedData.rightRef(4).toInt(&ok, 16);
                reversedData.chop(4);
                modifiedData.append(QString::number(intShort / 100)+ " ");
                modifiedData += QString::number(reversedData.rightRef(2).toUInt(&ok, 16) * 2) + ' ';
                reversedData.chop(2);
                appendNumber(2);
                intShort = reversedData.rightRef(2).toUInt(&ok, 16);
                if (intShort & 0x80){
                    intShort -= 0x100;
                }
                reversedData.chop(2);
                modifiedData.append(QString::number(intShort)+ " ");
                appendNumber(2);
                appendNumber(2);
            }
            if (packetType == 6){
                int count40 = 0, count32 = 0, count24 = 0, tempVal;
                int nsat = reversedData.rightRef(2).toInt(&ok, 16);
                appendNumber(2);

                for (int i = 0; i < nsat; i++){
                    reversedData.chop(2);
                    tempVal = reversedData.rightRef(2).toInt(&ok, 16);
                    reversedData.chop(2);

                    if (tempVal > 40){
                        count40++;
                    } else if (tempVal > 32){
                        count32++;
                    } else if (tempVal > 24){
                        count24++;
                    }
                }
                modifiedData += QString::number(count40) + ' ';
                modifiedData += QString::number(count32) + ' ';
                modifiedData += QString::number(count24) + ' ';
            }
        }
    }
    return modifiedData;
}

void GPSParser::StartTimer(){
    data->age = 0;
    if (!elapsedTime.isValid()){
        elapsedTime.start();
    } else {
        elapsedTime.restart();
    }
}

connectionStatus GPSParser::getStatus(){
    connectionStatus status;
    if (elapsedTime.isValid()){
        status.time = elapsedTime.elapsed() / 1000;
    }
    status.n_sat = data->n_sat;
    status.n_count_24 = data->n_count_24;
    status.n_count_32 = data->n_count_32;
    status.n_count_40 = data->n_count_40;
    return status;
}

