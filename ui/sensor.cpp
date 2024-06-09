#include "sensor.h"
#include "ui_sensor.h"

Q_DECLARE_METATYPE(GpsData)
Q_DECLARE_METATYPE(connectionStatus)
Q_DECLARE_METATYPE(Qt::ApplicationState)

Sensor::Sensor(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::Sensor)
    , m_serial(new QSerialPort(this))
{
    ui->setupUi(this);
    ui->portSelect->clear();

    qRegisterMetaType<GpsData>();
    qRegisterMetaType<connectionStatus>();
    qRegisterMetaType<Qt::ApplicationState>();

    // Connect the connection lambda function to the clicked signal of serialConnectionButton
    connect(ui->serialConnectionButton, &QPushButton::clicked, this, &Sensor::openSerialPort);
    connect(ui->serialLocalConnectionButton, &QPushButton::clicked, this, &Sensor::openSerialPort);

    // Connect the disconnection lambda function to the clicked signal of serialTerminationButton
    connect(ui->serialTerminationButton, &QPushButton::clicked, this, &Sensor::closeSerialPort);
    connect(ui->serialLocalTerminationButton, &QPushButton::clicked, this, &Sensor::closeSerialPort);

    connect(&m_thread, &SerialThread::error, this, &Sensor::handleError);
    connect(&m_thread, &SerialThread::dataReady, this, &Sensor::handleDataReady);
    connect(&m_thread, &SerialThread::dataStatus, this, &Sensor::handleConnectionStatus);
    connect(&m_thread, &SerialThread::appendData, this, &Sensor::appendOutputData);
    connect(this, &Sensor::clearFix, &m_thread, &SerialThread::clearFixSS);

    for (const QSerialPortInfo &serialPortInfo : QSerialPortInfo::availablePorts()) {
        ui->portSelect->addItem(serialPortInfo.portName());
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
        if (m_thread.isRunning()) {
            QTextStream(stdout) << tr("Warning: Force quit serialThread\n");
            m_thread.terminate();
            m_thread.wait();
        }
    }

    for (int i = 1; i <= 3; ++i) {
        delete values[i];
    }
    delete ui;
}

void Sensor::openSerialPort()
{
    QString path = ui->pathBrowser->toPlainText();
    setUIElementsEnabled(false);

    if (!path.isEmpty()) {
        m_thread.startLocalDataThread(path);
    } else {
        QString port = ui->portSelect->currentText();
        int baud = ui->baudSelect->currentText().toInt();
        bool save = ui->saveButton->isChecked();

        if (!port.isEmpty() && baud != 0) {
            m_thread.startSerialDataThread(port, baud, save);
            graphCount = 0;
        } else {
            handleError("Could not open port. Insufficient information provided.");
        }
    }
}

void Sensor::closeSerialPort()
{
    // Stop the thread gracefully
    m_thread.stopSerialThread();

    // Wait for the thread to finish
    if (!m_thread.wait(time)) {
        qWarning() << "Serial thread did not terminate in time, forcing termination...";
        m_thread.terminate();
        m_thread.wait();
    }

    // Close the serial port if it's still open
    if (m_serial->isOpen()) {
        m_serial->close();
        qDebug() << "Serial port closed.";
    }

    setUIElementsEnabled(true);

    // Check if thread has been properly stopped
    if (!m_thread.isRunning()) {
        QMessageBox::information(this, tr("Disconnected"), tr("Serial port closed successfully."));
    } else {
        QMessageBox::critical(this, tr("Critical Error"), tr("Failed to close the serial thread properly."));
        ui->ledIndicator->setState(QLedLabel::StateError);
    }
}

void Sensor::setUIElementsEnabled(bool enabled)
{
    ui->serialConnectionButton->setEnabled(enabled);
    ui->serialLocalConnectionButton->setEnabled(enabled);
    ui->serialTerminationButton->setEnabled(!enabled);
    ui->serialLocalTerminationButton->setEnabled(!enabled);
    ui->portSelect->setEnabled(enabled);
    ui->baudSelect->setEnabled(enabled);
    ui->saveButton->setEnabled(enabled);
    ui->ledIndicator->setState(enabled ? QLedLabel::StateOkBlue : QLedLabel::StateOk);
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
    ui->textbrowser->setText(tr("Time: %1\nLatitude: %2\nLongitude: %3\nAltitude: %4m\nRSSI: %5\nAge: %6s\nNo. of SAT: %7\nSat > 24: %8\nSat > 32: %9\nSat > 40: %10\nBatt Level: %11V\nHor Speed: %12m/s\nVer Speed: %13m/s\nPck Rec: %14\nPck Snt: %15\n").arg(data.time.toString("HH:mm:ss"),
                                                                                                                                                                                                                                              QString::number(data.latitude),
                                                                                                                                                                                                                                              QString::number(data.longitude),
                                                                                                                                                                                                                                              QString::number(data.altitude),
                                                                                                                                                                                                                                              QString::number(data.rssi),
                                                                                                                                                                                                                                              QString::number(data.age),
                                                                                                                                                                                                                                              QString::number(data.n_sat),
                                                                                                                                                                                                                                              QString::number(data.n_count_24),
                                                                                                                                                                                                                                              QString::number(data.n_count_32),
                                                                                                                                                                                                                                              QString::number(data.n_count_40),
                                                                                                                                                                                                                                              QString::number(data.battLevel),
                                                                                                                                                                                                                                              QString::number(data.horVelocity),
                                                                                                                                                                                                                                              QString::number(data.verVelocity),
                                                                                                                                                                                                                                              QString::number(data.pck_rcv),
                                                                                                                                                                                                                                              QString::number(data.pck_snt)
                                                                                                                                                                                                                                              ));

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
    QString text = QString("Connection Status: Time -> %1 | satellite -> %2 | count_24 -> %3 | count_32 -> %4 | count_40 -> %5</span>")
                                 .arg(QString::number(status.time),
                                      QString::number(status.n_sat),
                                      QString::number(status.n_count_24),
                                      QString::number(status.n_count_32),
                                      QString::number(status.n_count_40));
    appendOutputData(text, "#ff69b4");
    if (status.time < 0 || status.time > 5 || (status.n_count_24 < 2 && status.n_count_32 < 2 && status.n_count_40 < 2)) {
        ui->ledIndicator->setState(QLedLabel::StateError);
    } else if (status.time > 2 || (status.n_count_24 < 4 && status.n_count_32 < 4 && status.n_count_40 < 1)) {
        ui->ledIndicator->setState(QLedLabel::StateWarning);
    } else {
         ui->ledIndicator->setState(QLedLabel::StateOk);
    }
}

void Sensor::appendOutputData(const QString &data, const QString &color){
    ui->outputScreen->append(tr("<span style='color:%1;'> %2").arg(color, data));
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
    emit clearFix(0,0);
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
