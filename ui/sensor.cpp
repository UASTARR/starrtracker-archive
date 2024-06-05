#include "sensor.h"
#include "ui_sensor.h"

Q_DECLARE_METATYPE(GpsData)
Q_DECLARE_METATYPE(connectionStatus)

Sensor::Sensor(QWidget *parent):
    QWidget{parent},
    ui(new Ui::Sensor),
    m_serial( new QSerialPort(this) )
{
    ui->setupUi(this);
    ui->portSelect->clear();

    qRegisterMetaType<GpsData>();
    qRegisterMetaType<connectionStatus>();

    // Connect the connection lambda function to the clicked signal of serialConnectionButton
    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &Sensor::openSerialPort);
    connect(ui->serialLocalConnectionButton, &QPushButton::clicked, this, &Sensor::openSerialPort);

    // Connect the disconnection lambda function to the clicked signal of serialTerminationButton
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &Sensor::closeSerialPort);
    connect(ui->serialLocalTerminationButton, &QPushButton::clicked, this, &Sensor::closeSerialPort);

    connect(&m_thread, &SerialThread::error, this, &Sensor::handleError);
    connect(&m_thread, &SerialThread::dataReady, this, &Sensor::handleDataReady);
    connect(&m_thread, &SerialThread::dataStatus, this, &Sensor::handleConnectionStatus);

    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ui->portSelect->addItem(serialPortInfo.portName()); // If working in WSL 2, you need to pass the USB connection through for this to work.
    }

    // Setup Graph
    values[1] = new Graph(ui->graph_x);
    values[2] = new Graph(ui->graph_y);
    values[3] = new Graph(ui->graph_alt);
    values[1]->setGraph(-9000, 9000);
    values[2]->setGraph(-18000, 18000);
    values[3]->setGraph(0, 1800);

    // Setup Map
    ui->QW_Map->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    ui->QW_Map->show();

    auto Obje = ui->QW_Map->rootObject();
    connect(this, SIGNAL(setLocationMarker_1(QVariant, QVariant)), Obje, SLOT(setLocationMarker_1(QVariant, QVariant)));
    connect(this, SIGNAL(setLocationMarker_2(QVariant, QVariant)), Obje, SLOT(setLocationMarker_2(QVariant, QVariant)));
}

Sensor::~Sensor()
{
    if (m_serial->isOpen())
        m_serial->close();

    // If serialThread is still running, try closing port. If that doesn't work, serial thread is force closed
    if (m_thread.isRunning())
    {
        closeSerialPort();
        if (m_thread.isRunning())
        {
            QTextStream(stdout) <<  tr("Warning: Force quit serialThread\n");
            m_thread.terminate();
        }
    }

    delete values[1];
    delete values[2];
    delete values[3];
    delete ui;
}

void Sensor::openSerialPort()
{
    QString path = ui->pathBrowser->toPlainText();
    ui->portSelect->setEnabled(false);
    ui->baudSelect->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->serialConnectionButton->setEnabled(false);
    ui->serialLocalConnectionButton->setEnabled(false);
    ui->serialTerminationButton->setEnabled(true);
    ui->serialLocalTerminationButton->setEnabled(true);
    if (path != ""){
        m_thread.startLocalDataThread(path);
    } else {
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        if (availablePorts.isEmpty()) {
            // No ports are available
            qDebug() << "No serial ports available.";
            handleError("No Ports Available");
        } else {
            QString port = ui->portSelect->currentText();
            int baud = ui->baudSelect->currentText().toInt();
            bool save = ui->saveButton->isChecked();
            if (!port.isEmpty() and baud!=0){
                m_thread.startSerialDataThread(port, baud, save);
                graphCount = 0;
            } else
                handleError("Could not open port. Insufficent information provided");
        }
    }
}

void Sensor::closeSerialPort()
{
    if (m_serial->isOpen())
        m_serial->close();

    m_thread.stopSerialThread();
    if (m_thread.wait(time))
    {
        QMessageBox::information(this,tr("Disconnected"),tr("Wow! The serial port closed!"));
        ui->serialConnectionButton->setEnabled(true);
        ui->serialLocalConnectionButton->setEnabled(true);
        ui->serialTerminationButton->setEnabled(false);
        ui->serialLocalTerminationButton->setEnabled(false);
        ui->portSelect->setEnabled(true);
        ui->baudSelect->setEnabled(true);
        ui->saveButton->setEnabled(true);
        ui->ledIndicator->setState(QLedLabel::StateOkBlue);
    }
    else {
        ui->serialTerminationButton->setEnabled(true);
        ui->serialLocalTerminationButton->setEnabled(true);
        QMessageBox::critical(this, tr("Critical Error"), tr("Failed to close thread"));
        ui->ledIndicator->setState(QLedLabel::StateError);
    }
}

void Sensor::handleError(const QString &s)
{
    QMessageBox::critical(this, tr("Critical Error"), s);
}

void Sensor::handleDataReady(const GpsData &data)
{
    if (graphCount > checkCount){
        qt_time.removeFirst();
        qt_x.removeFirst();
        qt_y.removeFirst();
        qt_alt.removeFirst();
    } else {
        graphCount++;
    }

    qt_time.append(QTime(0,0,0).secsTo(data.time));
    qt_x.append(data.latitude);
    qt_y.append(data.longitude);
    qt_alt.append(data.altitude);

    ui->gpstype->setText(data.gps_name);
    ui->textbrowser->setText(tr("Time: %1\nLatitude: %2\nLongitude: %3\nAltitude: %4\nNo. of SAT: %5\nRSSI: %6\n").arg(data.time.toString("HH:mm:ss"), QString::number(data.latitude), QString::number(data.longitude), QString::number(data.altitude), QString::number(data.n_sat), QString::number(data.rssi)));

    if (lat == 0 && lon == 0){
        lat = data.latitude;
        lon = data.longitude;
        emit setLocationMarker_1(lat, lon);
    }

    emit setLocationMarker_2(data.latitude, data.longitude);

    values[1]->addGraph(qt_time, qt_x);
    values[2]->addGraph(qt_time, qt_y);
    values[3]->addGraph(qt_time, qt_alt);
}

void Sensor::handleConnectionStatus(const connectionStatus &status){
    qDebug() << "Connection Status: " << status.time << status.n_sat << status.n_count_24 << status.n_count_32 << status.n_count_40;
    if (status.time < 0 or status.time > 5 or (status.n_count_24 < 2 and status.n_count_32 < 2 and status.n_count_40 < 2)) {
        ui->ledIndicator->setState(QLedLabel::StateError);
    } else if (status.time > 2 or (status.n_count_24 < 4 and status.n_count_32 < 4 and status.n_count_40 < 1)) {
        ui->ledIndicator->setState(QLedLabel::StateWarning);
    } else {
         ui->ledIndicator->setState(QLedLabel::StateOk);
    }
}

void Sensor::writeData(const QByteArray &data) {
    m_serial->write(data);
}

void Sensor::on_next_clicked()
{
    ui->stackedDisplay->setCurrentIndex(1);
}

void Sensor::on_prev_clicked()
{
    ui->stackedDisplay->setCurrentIndex(0);
}

void Sensor::resetScreen()
{
    qt_time.clear();
    qt_x.clear();
    qt_y.clear();
    qt_alt.clear();
    graphCount = 0;
    values[1]->addGraph(qt_time, qt_x);
    values[2]->addGraph(qt_time, qt_y);
    values[3]->addGraph(qt_time, qt_alt);
    QQuickItem *rootItem = ui->QW_Map->rootObject();
    if (rootItem) {
        QMetaObject::invokeMethod(rootItem, "clearMarkers", Q_ARG(QVariant, 0));
        QMetaObject::invokeMethod(rootItem, "clearLine");
    }
    lat = 0;
    lon = 0;
}

void Sensor::on_resetBtn1_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation clear screen", "Are you sure you want to clear the display screen. The stored data will not be deleted.");
    if (reply == QMessageBox::Yes){
        resetScreen();
    }
}

void Sensor::on_resetBtn2_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation clear screen", "Are you sure you want to clear the display screen. The stored data will not be deleted.");
    if (reply == QMessageBox::Yes){
        resetScreen();
    }
}
